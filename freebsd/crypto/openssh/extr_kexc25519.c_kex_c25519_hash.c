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
typedef  int /*<<< orphan*/  u_char ;
struct sshbuf {int dummy; } ;

/* Variables and functions */
 size_t CURVE25519_SIZE ; 
 int /*<<< orphan*/  SSH2_MSG_KEXINIT ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 
 int /*<<< orphan*/  dump_digest (char*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ ssh_digest_buffer (int,struct sshbuf*,int /*<<< orphan*/ *,size_t) ; 
 size_t ssh_digest_bytes (int) ; 
 int /*<<< orphan*/  sshbuf_dump (struct sshbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 struct sshbuf* sshbuf_new () ; 
 int sshbuf_put (struct sshbuf*,int /*<<< orphan*/  const*,size_t) ; 
 int sshbuf_put_cstring (struct sshbuf*,char const*) ; 
 int sshbuf_put_string (struct sshbuf*,int /*<<< orphan*/  const*,size_t) ; 
 int sshbuf_put_u32 (struct sshbuf*,size_t) ; 
 int sshbuf_put_u8 (struct sshbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int
kex_c25519_hash(
    int hash_alg,
    const char *client_version_string,
    const char *server_version_string,
    const u_char *ckexinit, size_t ckexinitlen,
    const u_char *skexinit, size_t skexinitlen,
    const u_char *serverhostkeyblob, size_t sbloblen,
    const u_char client_dh_pub[CURVE25519_SIZE],
    const u_char server_dh_pub[CURVE25519_SIZE],
    const u_char *shared_secret, size_t secretlen,
    u_char *hash, size_t *hashlen)
{
	struct sshbuf *b;
	int r;

	if (*hashlen < ssh_digest_bytes(hash_alg))
		return SSH_ERR_INVALID_ARGUMENT;
	if ((b = sshbuf_new()) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	if ((r = sshbuf_put_cstring(b, client_version_string)) < 0 ||
	    (r = sshbuf_put_cstring(b, server_version_string)) < 0 ||
	    /* kexinit messages: fake header: len+SSH2_MSG_KEXINIT */
	    (r = sshbuf_put_u32(b, ckexinitlen+1)) < 0 ||
	    (r = sshbuf_put_u8(b, SSH2_MSG_KEXINIT)) < 0 ||
	    (r = sshbuf_put(b, ckexinit, ckexinitlen)) < 0 ||
	    (r = sshbuf_put_u32(b, skexinitlen+1)) < 0 ||
	    (r = sshbuf_put_u8(b, SSH2_MSG_KEXINIT)) < 0 ||
	    (r = sshbuf_put(b, skexinit, skexinitlen)) < 0 ||
	    (r = sshbuf_put_string(b, serverhostkeyblob, sbloblen)) < 0 ||
	    (r = sshbuf_put_string(b, client_dh_pub, CURVE25519_SIZE)) < 0 ||
	    (r = sshbuf_put_string(b, server_dh_pub, CURVE25519_SIZE)) < 0 ||
	    (r = sshbuf_put(b, shared_secret, secretlen)) < 0) {
		sshbuf_free(b);
		return r;
	}
#ifdef DEBUG_KEX
	sshbuf_dump(b, stderr);
#endif
	if (ssh_digest_buffer(hash_alg, b, hash, *hashlen) != 0) {
		sshbuf_free(b);
		return SSH_ERR_LIBCRYPTO_ERROR;
	}
	sshbuf_free(b);
	*hashlen = ssh_digest_bytes(hash_alg);
#ifdef DEBUG_KEX
	dump_digest("hash", hash, *hashlen);
#endif
	return 0;
}