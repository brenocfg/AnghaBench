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
struct kex {size_t session_id_len; int (* sign ) (struct sshkey*,struct sshkey*,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * dh; int /*<<< orphan*/  hostkey_alg; int /*<<< orphan*/ * session_id; int /*<<< orphan*/  my; int /*<<< orphan*/  peer; int /*<<< orphan*/  server_version_string; int /*<<< orphan*/  client_version_string; int /*<<< orphan*/  hash_alg; int /*<<< orphan*/  hostkey_nid; int /*<<< orphan*/  hostkey_type; struct sshkey* (* load_host_private_key ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ssh*) ;struct sshkey* (* load_host_public_key ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ssh*) ;} ;
typedef  int /*<<< orphan*/  hash ;
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* BN_new () ; 
 int /*<<< orphan*/  BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_print_fp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int DH_compute_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_get0_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 size_t DH_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DHparams_print_fp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSH2_MSG_KEXDH_REPLY ; 
 int SSH_DIGEST_MAX_LENGTH ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 
 int SSH_ERR_MESSAGE_INCOMPLETE ; 
 int SSH_ERR_NO_HOSTKEY_LOADED ; 
 int /*<<< orphan*/  debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dh_pub_is_valid (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dump_digest (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int kex_derive_keys_bn (struct ssh*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const*) ; 
 int kex_dh_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t*) ; 
 int kex_send_newkeys (struct ssh*) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sshbuf_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshbuf_ptr (int /*<<< orphan*/ ) ; 
 int sshkey_to_blob (struct sshkey*,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  sshpkt_disconnect (struct ssh*,char*) ; 
 int sshpkt_get_bignum2 (struct ssh*,int /*<<< orphan*/  const*) ; 
 int sshpkt_get_end (struct ssh*) ; 
 int sshpkt_put_bignum2 (struct ssh*,int /*<<< orphan*/  const*) ; 
 int sshpkt_put_string (struct ssh*,int /*<<< orphan*/ *,size_t) ; 
 int sshpkt_send (struct ssh*) ; 
 int sshpkt_start (struct ssh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 struct sshkey* stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ssh*) ; 
 struct sshkey* stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ssh*) ; 
 int stub3 (struct sshkey*,struct sshkey*,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
input_kex_dh_init(int type, u_int32_t seq, struct ssh *ssh)
{
	struct kex *kex = ssh->kex;
	BIGNUM *shared_secret = NULL, *dh_client_pub = NULL;
	const BIGNUM *pub_key;
	struct sshkey *server_host_public, *server_host_private;
	u_char *kbuf = NULL, *signature = NULL, *server_host_key_blob = NULL;
	u_char hash[SSH_DIGEST_MAX_LENGTH];
	size_t sbloblen, slen;
	size_t klen = 0, hashlen;
	int kout, r;

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

	/* key, cert */
	if ((dh_client_pub = BN_new()) == NULL) {
		r = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	DH_get0_key(kex->dh, &pub_key, NULL);
	if ((r = sshpkt_get_bignum2(ssh, dh_client_pub)) != 0 ||
	    (r = sshpkt_get_end(ssh)) != 0)
		goto out;

#ifdef DEBUG_KEXDH
	fprintf(stderr, "dh_client_pub= ");
	BN_print_fp(stderr, dh_client_pub);
	fprintf(stderr, "\n");
	debug("bits %d", BN_num_bits(dh_client_pub));
	DHparams_print_fp(stderr, kex->dh);
	fprintf(stderr, "pub= ");
	BN_print_fp(stderr, pub_key);
	fprintf(stderr, "\n");
#endif
	if (!dh_pub_is_valid(kex->dh, dh_client_pub)) {
		sshpkt_disconnect(ssh, "bad client public DH value");
		r = SSH_ERR_MESSAGE_INCOMPLETE;
		goto out;
	}

	klen = DH_size(kex->dh);
	if ((kbuf = malloc(klen)) == NULL ||
	    (shared_secret = BN_new()) == NULL) {
		r = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	if ((kout = DH_compute_key(kbuf, dh_client_pub, kex->dh)) < 0 ||
	    BN_bin2bn(kbuf, kout, shared_secret) == NULL) {
		r = SSH_ERR_LIBCRYPTO_ERROR;
		goto out;
	}
#ifdef DEBUG_KEXDH
	dump_digest("shared secret", kbuf, kout);
#endif
	if ((r = sshkey_to_blob(server_host_public, &server_host_key_blob,
	    &sbloblen)) != 0)
		goto out;
	/* calc H */
	hashlen = sizeof(hash);
	if ((r = kex_dh_hash(
	    kex->hash_alg,
	    kex->client_version_string,
	    kex->server_version_string,
	    sshbuf_ptr(kex->peer), sshbuf_len(kex->peer),
	    sshbuf_ptr(kex->my), sshbuf_len(kex->my),
	    server_host_key_blob, sbloblen,
	    dh_client_pub,
	    pub_key,
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

	/* send server hostkey, DH pubkey 'f' and signed H */
	if ((r = sshpkt_start(ssh, SSH2_MSG_KEXDH_REPLY)) != 0 ||
	    (r = sshpkt_put_string(ssh, server_host_key_blob, sbloblen)) != 0 ||
	    (r = sshpkt_put_bignum2(ssh, pub_key)) != 0 ||	/* f */
	    (r = sshpkt_put_string(ssh, signature, slen)) != 0 ||
	    (r = sshpkt_send(ssh)) != 0)
		goto out;

	if ((r = kex_derive_keys_bn(ssh, hash, hashlen, shared_secret)) == 0)
		r = kex_send_newkeys(ssh);
 out:
	explicit_bzero(hash, sizeof(hash));
	DH_free(kex->dh);
	kex->dh = NULL;
	BN_clear_free(dh_client_pub);
	if (kbuf) {
		explicit_bzero(kbuf, klen);
		free(kbuf);
	}
	BN_clear_free(shared_secret);
	free(server_host_key_blob);
	free(signature);
	return r;
}