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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct sshkey {scalar_t__ type; scalar_t__ ecdsa_nid; } ;
struct sshbuf {int dummy; } ;
struct ssh {int /*<<< orphan*/  compat; struct kex* kex; } ;
struct kex {int (* verify_host_key ) (struct sshkey*,struct ssh*) ;scalar_t__ hostkey_type; scalar_t__ hostkey_nid; size_t session_id_len; int /*<<< orphan*/ * c25519_client_key; int /*<<< orphan*/ * session_id; int /*<<< orphan*/  hostkey_alg; int /*<<< orphan*/  c25519_client_pubkey; struct sshbuf* peer; struct sshbuf* my; int /*<<< orphan*/  server_version_string; int /*<<< orphan*/  client_version_string; int /*<<< orphan*/  hash_alg; } ;
typedef  int /*<<< orphan*/  hash ;

/* Variables and functions */
 size_t CURVE25519_SIZE ; 
 scalar_t__ KEY_ECDSA ; 
 int SSH_DIGEST_MAX_LENGTH ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int SSH_ERR_KEY_TYPE_MISMATCH ; 
 int SSH_ERR_SIGNATURE_INVALID ; 
 int /*<<< orphan*/  dump_digest (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int kex_c25519_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 int kex_derive_keys (struct ssh*,int /*<<< orphan*/ *,size_t,struct sshbuf*) ; 
 int kex_send_newkeys (struct ssh*) ; 
 int kexc25519_shared_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sshbuf*) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_len (struct sshbuf*) ; 
 struct sshbuf* sshbuf_new () ; 
 int /*<<< orphan*/  sshbuf_ptr (struct sshbuf*) ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey*) ; 
 int sshkey_from_blob (int /*<<< orphan*/ *,size_t,struct sshkey**) ; 
 int sshkey_verify (struct sshkey*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sshpkt_get_end (struct ssh*) ; 
 int sshpkt_get_string (struct ssh*,int /*<<< orphan*/ **,size_t*) ; 
 int stub1 (struct sshkey*,struct ssh*) ; 

__attribute__((used)) static int
input_kex_c25519_reply(int type, u_int32_t seq, struct ssh *ssh)
{
	struct kex *kex = ssh->kex;
	struct sshkey *server_host_key = NULL;
	struct sshbuf *shared_secret = NULL;
	u_char *server_pubkey = NULL;
	u_char *server_host_key_blob = NULL, *signature = NULL;
	u_char hash[SSH_DIGEST_MAX_LENGTH];
	size_t slen, pklen, sbloblen, hashlen;
	int r;

	if (kex->verify_host_key == NULL) {
		r = SSH_ERR_INVALID_ARGUMENT;
		goto out;
	}

	/* hostkey */
	if ((r = sshpkt_get_string(ssh, &server_host_key_blob,
	    &sbloblen)) != 0 ||
	    (r = sshkey_from_blob(server_host_key_blob, sbloblen,
	    &server_host_key)) != 0)
		goto out;
	if (server_host_key->type != kex->hostkey_type ||
	    (kex->hostkey_type == KEY_ECDSA &&
	    server_host_key->ecdsa_nid != kex->hostkey_nid)) {
		r = SSH_ERR_KEY_TYPE_MISMATCH;
		goto out;
	}
	if (kex->verify_host_key(server_host_key, ssh) == -1) {
		r = SSH_ERR_SIGNATURE_INVALID;
		goto out;
	}

	/* Q_S, server public key */
	/* signed H */
	if ((r = sshpkt_get_string(ssh, &server_pubkey, &pklen)) != 0 ||
	    (r = sshpkt_get_string(ssh, &signature, &slen)) != 0 ||
	    (r = sshpkt_get_end(ssh)) != 0)
		goto out;
	if (pklen != CURVE25519_SIZE) {
		r = SSH_ERR_SIGNATURE_INVALID;
		goto out;
	}

#ifdef DEBUG_KEXECDH
	dump_digest("server public key:", server_pubkey, CURVE25519_SIZE);
#endif

	if ((shared_secret = sshbuf_new()) == NULL) {
		r = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	if ((r = kexc25519_shared_key(kex->c25519_client_key, server_pubkey,
	    shared_secret)) < 0)
		goto out;

	/* calc and verify H */
	hashlen = sizeof(hash);
	if ((r = kex_c25519_hash(
	    kex->hash_alg,
	    kex->client_version_string,
	    kex->server_version_string,
	    sshbuf_ptr(kex->my), sshbuf_len(kex->my),
	    sshbuf_ptr(kex->peer), sshbuf_len(kex->peer),
	    server_host_key_blob, sbloblen,
	    kex->c25519_client_pubkey,
	    server_pubkey,
	    sshbuf_ptr(shared_secret), sshbuf_len(shared_secret),
	    hash, &hashlen)) < 0)
		goto out;

	if ((r = sshkey_verify(server_host_key, signature, slen, hash, hashlen,
	    kex->hostkey_alg, ssh->compat)) != 0)
		goto out;

	/* save session id */
	if (kex->session_id == NULL) {
		kex->session_id_len = hashlen;
		kex->session_id = malloc(kex->session_id_len);
		if (kex->session_id == NULL) {
			r = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		memcpy(kex->session_id, hash, kex->session_id_len);
	}

	if ((r = kex_derive_keys(ssh, hash, hashlen, shared_secret)) == 0)
		r = kex_send_newkeys(ssh);
out:
	explicit_bzero(hash, sizeof(hash));
	explicit_bzero(kex->c25519_client_key, sizeof(kex->c25519_client_key));
	free(server_host_key_blob);
	free(server_pubkey);
	free(signature);
	sshkey_free(server_host_key);
	sshbuf_free(shared_secret);
	return r;
}