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
struct ssh {int /*<<< orphan*/  compat; struct kex* kex; } ;
struct kex {size_t session_id_len; int (* sign ) (struct sshkey*,struct sshkey*,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * ec_client_key; int /*<<< orphan*/  hostkey_alg; int /*<<< orphan*/ * session_id; int /*<<< orphan*/  my; int /*<<< orphan*/  peer; int /*<<< orphan*/  server_version_string; int /*<<< orphan*/  client_version_string; int /*<<< orphan*/  hash_alg; int /*<<< orphan*/  hostkey_nid; int /*<<< orphan*/  hostkey_type; struct sshkey* (* load_host_private_key ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ssh*) ;struct sshkey* (* load_host_public_key ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ssh*) ;int /*<<< orphan*/  ec_nid; } ;
typedef  int /*<<< orphan*/  hash ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int ECDH_compute_key (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EC_GROUP_get_degree (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int EC_KEY_generate_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_get0_group (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_get0_public_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_new_by_curve_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EC_POINT_new (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SSH2_MSG_KEX_ECDH_REPLY ; 
 int SSH_DIGEST_MAX_LENGTH ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 
 int SSH_ERR_MESSAGE_INCOMPLETE ; 
 int SSH_ERR_NO_HOSTKEY_LOADED ; 
 int /*<<< orphan*/  dump_digest (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int kex_derive_keys_bn (struct ssh*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int kex_ecdh_hash (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 
 int kex_send_newkeys (struct ssh*) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sshbuf_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshbuf_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshkey_dump_ec_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sshkey_dump_ec_point (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ sshkey_ec_validate_public (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int sshkey_to_blob (struct sshkey*,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  sshpkt_disconnect (struct ssh*,char*) ; 
 int sshpkt_get_ec (struct ssh*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int sshpkt_get_end (struct ssh*) ; 
 int sshpkt_put_ec (struct ssh*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int sshpkt_put_string (struct ssh*,int /*<<< orphan*/ *,size_t) ; 
 int sshpkt_send (struct ssh*) ; 
 int sshpkt_start (struct ssh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 struct sshkey* stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ssh*) ; 
 struct sshkey* stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ssh*) ; 
 int stub3 (struct sshkey*,struct sshkey*,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
input_kex_ecdh_init(int type, u_int32_t seq, struct ssh *ssh)
{
	struct kex *kex = ssh->kex;
	EC_POINT *client_public;
	EC_KEY *server_key = NULL;
	const EC_GROUP *group;
	const EC_POINT *public_key;
	BIGNUM *shared_secret = NULL;
	struct sshkey *server_host_private, *server_host_public;
	u_char *server_host_key_blob = NULL, *signature = NULL;
	u_char *kbuf = NULL;
	u_char hash[SSH_DIGEST_MAX_LENGTH];
	size_t slen, sbloblen;
	size_t klen = 0, hashlen;
	int r;

	if ((server_key = EC_KEY_new_by_curve_name(kex->ec_nid)) == NULL) {
		r = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	if (EC_KEY_generate_key(server_key) != 1) {
		r = SSH_ERR_LIBCRYPTO_ERROR;
		goto out;
	}
	group = EC_KEY_get0_group(server_key);

#ifdef DEBUG_KEXECDH
	fputs("server private key:\n", stderr);
	sshkey_dump_ec_key(server_key);
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
	if ((client_public = EC_POINT_new(group)) == NULL) {
		r = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	if ((r = sshpkt_get_ec(ssh, client_public, group)) != 0 ||
	    (r = sshpkt_get_end(ssh)) != 0)
		goto out;

#ifdef DEBUG_KEXECDH
	fputs("client public key:\n", stderr);
	sshkey_dump_ec_point(group, client_public);
#endif
	if (sshkey_ec_validate_public(group, client_public) != 0) {
		sshpkt_disconnect(ssh, "invalid client public key");
		r = SSH_ERR_MESSAGE_INCOMPLETE;
		goto out;
	}

	/* Calculate shared_secret */
	klen = (EC_GROUP_get_degree(group) + 7) / 8;
	if ((kbuf = malloc(klen)) == NULL ||
	    (shared_secret = BN_new()) == NULL) {
		r = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	if (ECDH_compute_key(kbuf, klen, client_public,
	    server_key, NULL) != (int)klen ||
	    BN_bin2bn(kbuf, klen, shared_secret) == NULL) {
		r = SSH_ERR_LIBCRYPTO_ERROR;
		goto out;
	}

#ifdef DEBUG_KEXECDH
	dump_digest("shared secret", kbuf, klen);
#endif
	/* calc H */
	if ((r = sshkey_to_blob(server_host_public, &server_host_key_blob,
	    &sbloblen)) != 0)
		goto out;
	hashlen = sizeof(hash);
	if ((r = kex_ecdh_hash(
	    kex->hash_alg,
	    group,
	    kex->client_version_string,
	    kex->server_version_string,
	    sshbuf_ptr(kex->peer), sshbuf_len(kex->peer),
	    sshbuf_ptr(kex->my), sshbuf_len(kex->my),
	    server_host_key_blob, sbloblen,
	    client_public,
	    EC_KEY_get0_public_key(server_key),
	    shared_secret,
	    hash, &hashlen)) != 0)
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

	/* destroy_sensitive_data(); */

	public_key = EC_KEY_get0_public_key(server_key);
	/* send server hostkey, ECDH pubkey 'Q_S' and signed H */
	if ((r = sshpkt_start(ssh, SSH2_MSG_KEX_ECDH_REPLY)) != 0 ||
	    (r = sshpkt_put_string(ssh, server_host_key_blob, sbloblen)) != 0 ||
	    (r = sshpkt_put_ec(ssh, public_key, group)) != 0 ||
	    (r = sshpkt_put_string(ssh, signature, slen)) != 0 ||
	    (r = sshpkt_send(ssh)) != 0)
		goto out;

	if ((r = kex_derive_keys_bn(ssh, hash, hashlen, shared_secret)) == 0)
		r = kex_send_newkeys(ssh);
 out:
	explicit_bzero(hash, sizeof(hash));
	EC_KEY_free(kex->ec_client_key);
	kex->ec_client_key = NULL;
	EC_KEY_free(server_key);
	if (kbuf) {
		explicit_bzero(kbuf, klen);
		free(kbuf);
	}
	BN_clear_free(shared_secret);
	free(server_host_key_blob);
	free(signature);
	return r;
}