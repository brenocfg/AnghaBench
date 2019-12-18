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
struct ssh {int compat; struct kex* kex; } ;
struct kex {int (* verify_host_key ) (struct sshkey*,struct ssh*) ;scalar_t__ hostkey_type; scalar_t__ hostkey_nid; int min; int max; size_t session_id_len; int /*<<< orphan*/ * dh; int /*<<< orphan*/ * session_id; int /*<<< orphan*/  hostkey_alg; int /*<<< orphan*/  nbits; int /*<<< orphan*/  peer; int /*<<< orphan*/  my; int /*<<< orphan*/  server_version_string; int /*<<< orphan*/  client_version_string; int /*<<< orphan*/  hash_alg; } ;
typedef  int /*<<< orphan*/  hash ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_num_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_print_fp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int DH_compute_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_get0_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_get0_pqg (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 size_t DH_size (int /*<<< orphan*/ *) ; 
 scalar_t__ KEY_ECDSA ; 
 int SSH_DIGEST_MAX_LENGTH ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int SSH_ERR_KEY_TYPE_MISMATCH ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 
 int SSH_ERR_MESSAGE_INCOMPLETE ; 
 int SSH_ERR_SIGNATURE_INVALID ; 
 int SSH_OLD_DHGEX ; 
 int /*<<< orphan*/  debug (char*,...) ; 
 int /*<<< orphan*/  dh_pub_is_valid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_digest (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int kex_derive_keys_bn (struct ssh*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int kex_send_newkeys (struct ssh*) ; 
 int kexgex_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sshbuf_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshbuf_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey*) ; 
 int sshkey_from_blob (int /*<<< orphan*/ *,size_t,struct sshkey**) ; 
 int sshkey_verify (struct sshkey*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sshpkt_disconnect (struct ssh*,char*) ; 
 int sshpkt_get_bignum2 (struct ssh*,int /*<<< orphan*/ *) ; 
 int sshpkt_get_end (struct ssh*) ; 
 int sshpkt_get_string (struct ssh*,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  stderr ; 
 int stub1 (struct sshkey*,struct ssh*) ; 

__attribute__((used)) static int
input_kex_dh_gex_reply(int type, u_int32_t seq, struct ssh *ssh)
{
	struct kex *kex = ssh->kex;
	BIGNUM *dh_server_pub = NULL, *shared_secret = NULL;
	const BIGNUM *pub_key, *dh_p, *dh_g;
	struct sshkey *server_host_key = NULL;
	u_char *kbuf = NULL, *signature = NULL, *server_host_key_blob = NULL;
	u_char hash[SSH_DIGEST_MAX_LENGTH];
	size_t klen = 0, slen, sbloblen, hashlen;
	int kout, r;

	debug("got SSH2_MSG_KEX_DH_GEX_REPLY");
	if (kex->verify_host_key == NULL) {
		r = SSH_ERR_INVALID_ARGUMENT;
		goto out;
	}
	/* key, cert */
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
	/* DH parameter f, server public DH key */
	if ((dh_server_pub = BN_new()) == NULL) {
		r = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	/* signed H */
	if ((r = sshpkt_get_bignum2(ssh, dh_server_pub)) != 0 ||
	    (r = sshpkt_get_string(ssh, &signature, &slen)) != 0 ||
	    (r = sshpkt_get_end(ssh)) != 0)
		goto out;
#ifdef DEBUG_KEXDH
	fprintf(stderr, "dh_server_pub= ");
	BN_print_fp(stderr, dh_server_pub);
	fprintf(stderr, "\n");
	debug("bits %d", BN_num_bits(dh_server_pub));
#endif
	if (!dh_pub_is_valid(kex->dh, dh_server_pub)) {
		sshpkt_disconnect(ssh, "bad server public DH value");
		r = SSH_ERR_MESSAGE_INCOMPLETE;
		goto out;
	}

	klen = DH_size(kex->dh);
	if ((kbuf = malloc(klen)) == NULL ||
	    (shared_secret = BN_new()) == NULL) {
		r = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	if ((kout = DH_compute_key(kbuf, dh_server_pub, kex->dh)) < 0 ||
	    BN_bin2bn(kbuf, kout, shared_secret) == NULL) {
		r = SSH_ERR_LIBCRYPTO_ERROR;
		goto out;
	}
#ifdef DEBUG_KEXDH
	dump_digest("shared secret", kbuf, kout);
#endif
	if (ssh->compat & SSH_OLD_DHGEX)
		kex->min = kex->max = -1;

	/* calc and verify H */
	DH_get0_key(kex->dh, &pub_key, NULL);
	DH_get0_pqg(kex->dh, &dh_p, NULL, &dh_g);
	hashlen = sizeof(hash);
	if ((r = kexgex_hash(
	    kex->hash_alg,
	    kex->client_version_string,
	    kex->server_version_string,
	    sshbuf_ptr(kex->my), sshbuf_len(kex->my),
	    sshbuf_ptr(kex->peer), sshbuf_len(kex->peer),
	    server_host_key_blob, sbloblen,
	    kex->min, kex->nbits, kex->max,
	    dh_p, dh_g,
	    pub_key,
	    dh_server_pub,
	    shared_secret,
	    hash, &hashlen)) != 0)
		goto out;

	if ((r = sshkey_verify(server_host_key, signature, slen, hash,
	    hashlen, kex->hostkey_alg, ssh->compat)) != 0)
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

	if ((r = kex_derive_keys_bn(ssh, hash, hashlen, shared_secret)) == 0)
		r = kex_send_newkeys(ssh);
 out:
	explicit_bzero(hash, sizeof(hash));
	DH_free(kex->dh);
	kex->dh = NULL;
	BN_clear_free(dh_server_pub);
	if (kbuf) {
		explicit_bzero(kbuf, klen);
		free(kbuf);
	}
	BN_clear_free(shared_secret);
	sshkey_free(server_host_key);
	free(server_host_key_blob);
	free(signature);
	return r;
}