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
struct sshkey {int dummy; } ;
struct sshbuf {int dummy; } ;
struct ssh {int /*<<< orphan*/  compat; struct kex* kex; } ;
struct kex {size_t session_id_len; int (* sign ) (struct sshkey*,struct sshkey*,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  hostkey_alg; int /*<<< orphan*/ * session_id; struct sshbuf* my; struct sshbuf* peer; int /*<<< orphan*/  server_version_string; int /*<<< orphan*/  client_version_string; int /*<<< orphan*/  hash_alg; int /*<<< orphan*/  hostkey_nid; int /*<<< orphan*/  hostkey_type; struct sshkey* (* load_host_private_key ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ssh*) ;struct sshkey* (* load_host_public_key ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ssh*) ;} ;
typedef  int /*<<< orphan*/  server_pubkey ;
typedef  int /*<<< orphan*/  server_key ;
typedef  int /*<<< orphan*/  hash ;

/* Variables and functions */
 int CURVE25519_SIZE ; 
 int /*<<< orphan*/  SSH2_MSG_KEX_ECDH_REPLY ; 
 int SSH_DIGEST_MAX_LENGTH ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int SSH_ERR_NO_HOSTKEY_LOADED ; 
 int SSH_ERR_SIGNATURE_INVALID ; 
 int /*<<< orphan*/  dump_digest (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int kex_c25519_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 int kex_derive_keys (struct ssh*,int /*<<< orphan*/ *,size_t,struct sshbuf*) ; 
 int kex_send_newkeys (struct ssh*) ; 
 int /*<<< orphan*/  kexc25519_keygen (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int kexc25519_shared_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sshbuf*) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_len (struct sshbuf*) ; 
 struct sshbuf* sshbuf_new () ; 
 int /*<<< orphan*/  sshbuf_ptr (struct sshbuf*) ; 
 int sshkey_to_blob (struct sshkey*,int /*<<< orphan*/ **,size_t*) ; 
 int sshpkt_get_end (struct ssh*) ; 
 int sshpkt_get_string (struct ssh*,int /*<<< orphan*/ **,size_t*) ; 
 int sshpkt_put_string (struct ssh*,int /*<<< orphan*/ *,size_t) ; 
 int sshpkt_send (struct ssh*) ; 
 int sshpkt_start (struct ssh*,int /*<<< orphan*/ ) ; 
 struct sshkey* stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ssh*) ; 
 struct sshkey* stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ssh*) ; 
 int stub3 (struct sshkey*,struct sshkey*,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
input_kex_c25519_init(int type, u_int32_t seq, struct ssh *ssh)
{
	struct kex *kex = ssh->kex;
	struct sshkey *server_host_private, *server_host_public;
	struct sshbuf *shared_secret = NULL;
	u_char *server_host_key_blob = NULL, *signature = NULL;
	u_char server_key[CURVE25519_SIZE];
	u_char *client_pubkey = NULL;
	u_char server_pubkey[CURVE25519_SIZE];
	u_char hash[SSH_DIGEST_MAX_LENGTH];
	size_t slen, pklen, sbloblen, hashlen;
	int r;

	/* generate private key */
	kexc25519_keygen(server_key, server_pubkey);
#ifdef DEBUG_KEXECDH
	dump_digest("server private key:", server_key, sizeof(server_key));
#endif
	if (kex->load_host_public_key == NULL ||
	    kex->load_host_private_key == NULL) {
		r = SSH_ERR_INVALID_ARGUMENT;
		goto out;
	}
	server_host_public = kex->load_host_public_key(kex->hostkey_type,
	    kex->hostkey_nid, ssh);
	server_host_private = kex->load_host_private_key(kex->hostkey_type,
	    kex->hostkey_nid, ssh);
	if (server_host_public == NULL) {
		r = SSH_ERR_NO_HOSTKEY_LOADED;
		goto out;
	}

	if ((r = sshpkt_get_string(ssh, &client_pubkey, &pklen)) != 0 ||
	    (r = sshpkt_get_end(ssh)) != 0)
		goto out;
	if (pklen != CURVE25519_SIZE) {
		r = SSH_ERR_SIGNATURE_INVALID;
		goto out;
	}
#ifdef DEBUG_KEXECDH
	dump_digest("client public key:", client_pubkey, CURVE25519_SIZE);
#endif

	if ((shared_secret = sshbuf_new()) == NULL) {
		r = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	if ((r = kexc25519_shared_key(server_key, client_pubkey,
	    shared_secret)) < 0)
		goto out;

	/* calc H */
	if ((r = sshkey_to_blob(server_host_public, &server_host_key_blob,
	    &sbloblen)) != 0)
		goto out;
	hashlen = sizeof(hash);
	if ((r = kex_c25519_hash(
	    kex->hash_alg,
	    kex->client_version_string,
	    kex->server_version_string,
	    sshbuf_ptr(kex->peer), sshbuf_len(kex->peer),
	    sshbuf_ptr(kex->my), sshbuf_len(kex->my),
	    server_host_key_blob, sbloblen,
	    client_pubkey,
	    server_pubkey,
	    sshbuf_ptr(shared_secret), sshbuf_len(shared_secret),
	    hash, &hashlen)) < 0)
		goto out;

	/* save session id := H */
	if (kex->session_id == NULL) {
		kex->session_id_len = hashlen;
		kex->session_id = malloc(kex->session_id_len);
		if (kex->session_id == NULL) {
			r = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		memcpy(kex->session_id, hash, kex->session_id_len);
	}

	/* sign H */
	if ((r = kex->sign(server_host_private, server_host_public, &signature,
	     &slen, hash, hashlen, kex->hostkey_alg, ssh->compat)) < 0)
		goto out;

	/* send server hostkey, ECDH pubkey 'Q_S' and signed H */
	if ((r = sshpkt_start(ssh, SSH2_MSG_KEX_ECDH_REPLY)) != 0 ||
	    (r = sshpkt_put_string(ssh, server_host_key_blob, sbloblen)) != 0 ||
	    (r = sshpkt_put_string(ssh, server_pubkey, sizeof(server_pubkey))) != 0 ||
	    (r = sshpkt_put_string(ssh, signature, slen)) != 0 ||
	    (r = sshpkt_send(ssh)) != 0)
		goto out;

	if ((r = kex_derive_keys(ssh, hash, hashlen, shared_secret)) == 0)
		r = kex_send_newkeys(ssh);
out:
	explicit_bzero(hash, sizeof(hash));
	explicit_bzero(server_key, sizeof(server_key));
	free(server_host_key_blob);
	free(signature);
	free(client_pubkey);
	sshbuf_free(shared_secret);
	return r;
}