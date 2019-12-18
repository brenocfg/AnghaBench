#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t u_int ;
typedef  char u_char ;
struct sshbuf {int dummy; } ;
struct ssh_digest_ctx {int dummy; } ;
struct ssh {struct kex* kex; } ;
struct kex {char* session_id; size_t session_id_len; int /*<<< orphan*/  hash_alg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROUNDUP (size_t,size_t) ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 
 char* calloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_digest (char*,char*,size_t) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char) ; 
 int /*<<< orphan*/  free (char*) ; 
 size_t ssh_digest_bytes (int /*<<< orphan*/ ) ; 
 scalar_t__ ssh_digest_final (struct ssh_digest_ctx*,char*,size_t) ; 
 int /*<<< orphan*/  ssh_digest_free (struct ssh_digest_ctx*) ; 
 struct ssh_digest_ctx* ssh_digest_start (int /*<<< orphan*/ ) ; 
 scalar_t__ ssh_digest_update (struct ssh_digest_ctx*,char*,size_t) ; 
 scalar_t__ ssh_digest_update_buffer (struct ssh_digest_ctx*,struct sshbuf const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
derive_key(struct ssh *ssh, int id, u_int need, u_char *hash, u_int hashlen,
    const struct sshbuf *shared_secret, u_char **keyp)
{
	struct kex *kex = ssh->kex;
	struct ssh_digest_ctx *hashctx = NULL;
	char c = id;
	u_int have;
	size_t mdsz;
	u_char *digest;
	int r;

	if ((mdsz = ssh_digest_bytes(kex->hash_alg)) == 0)
		return SSH_ERR_INVALID_ARGUMENT;
	if ((digest = calloc(1, ROUNDUP(need, mdsz))) == NULL) {
		r = SSH_ERR_ALLOC_FAIL;
		goto out;
	}

	/* K1 = HASH(K || H || "A" || session_id) */
	if ((hashctx = ssh_digest_start(kex->hash_alg)) == NULL ||
	    ssh_digest_update_buffer(hashctx, shared_secret) != 0 ||
	    ssh_digest_update(hashctx, hash, hashlen) != 0 ||
	    ssh_digest_update(hashctx, &c, 1) != 0 ||
	    ssh_digest_update(hashctx, kex->session_id,
	    kex->session_id_len) != 0 ||
	    ssh_digest_final(hashctx, digest, mdsz) != 0) {
		r = SSH_ERR_LIBCRYPTO_ERROR;
		goto out;
	}
	ssh_digest_free(hashctx);
	hashctx = NULL;

	/*
	 * expand key:
	 * Kn = HASH(K || H || K1 || K2 || ... || Kn-1)
	 * Key = K1 || K2 || ... || Kn
	 */
	for (have = mdsz; need > have; have += mdsz) {
		if ((hashctx = ssh_digest_start(kex->hash_alg)) == NULL ||
		    ssh_digest_update_buffer(hashctx, shared_secret) != 0 ||
		    ssh_digest_update(hashctx, hash, hashlen) != 0 ||
		    ssh_digest_update(hashctx, digest, have) != 0 ||
		    ssh_digest_final(hashctx, digest + have, mdsz) != 0) {
			r = SSH_ERR_LIBCRYPTO_ERROR;
			goto out;
		}
		ssh_digest_free(hashctx);
		hashctx = NULL;
	}
#ifdef DEBUG_KEX
	fprintf(stderr, "key '%c'== ", c);
	dump_digest("key", digest, need);
#endif
	*keyp = digest;
	digest = NULL;
	r = 0;
 out:
	free(digest);
	ssh_digest_free(hashctx);
	return r;
}