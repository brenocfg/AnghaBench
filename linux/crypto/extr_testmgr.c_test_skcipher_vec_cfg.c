#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct testvec_config {scalar_t__ req_flags; int iv_offset; int /*<<< orphan*/  name; scalar_t__ nosimd; scalar_t__ iv_offset_relative_to_alignmask; } ;
struct TYPE_4__ {scalar_t__ complete; scalar_t__ const flags; int /*<<< orphan*/ * data; } ;
struct skcipher_request {scalar_t__ src; scalar_t__ dst; TYPE_1__ base; int /*<<< orphan*/ * iv; int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  __ctx; } ;
struct kvec {int /*<<< orphan*/  iov_len; void* iov_base; } ;
struct crypto_skcipher {int dummy; } ;
struct cipher_testvec {int setkey_error; int crypt_error; int /*<<< orphan*/  iv_out; int /*<<< orphan*/  len; scalar_t__ ptext; scalar_t__ ctext; scalar_t__ generates_iv; int /*<<< orphan*/  iv; int /*<<< orphan*/  klen; int /*<<< orphan*/  key; scalar_t__ wk; } ;
struct TYPE_5__ {scalar_t__ sgl_ptr; scalar_t__ sgl; } ;
struct cipher_test_sglists {TYPE_2__ dst; TYPE_2__ src; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_FORBID_WEAK_KEYS ; 
 scalar_t__ CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int /*<<< orphan*/  DECLARE_CRYPTO_WAIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EOVERFLOW ; 
 int MAX_ALGAPI_ALIGNMASK ; 
 int MAX_IVLEN ; 
 int /*<<< orphan*/ * PTR_ALIGN (int /*<<< orphan*/ *,int) ; 
 scalar_t__ WARN_ON (int) ; 
 int build_cipher_test_sglists (struct cipher_test_sglists*,struct testvec_config const*,unsigned int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kvec*,int) ; 
 int /*<<< orphan*/  crypto_disable_simd_for_test () ; 
 int /*<<< orphan*/  crypto_reenable_simd_for_test () ; 
 scalar_t__ crypto_req_done ; 
 unsigned int crypto_skcipher_alignmask (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_skcipher_clear_flags (struct crypto_skcipher*,int /*<<< orphan*/ ) ; 
 int crypto_skcipher_decrypt (struct skcipher_request*) ; 
 int crypto_skcipher_encrypt (struct skcipher_request*) ; 
 int /*<<< orphan*/  crypto_skcipher_get_flags (struct crypto_skcipher*) ; 
 unsigned int crypto_skcipher_ivsize (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_skcipher_reqsize (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int /*<<< orphan*/  crypto_skcipher_set_flags (struct crypto_skcipher*,int /*<<< orphan*/ ) ; 
 int crypto_skcipher_setkey (struct crypto_skcipher*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_wait_req (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hexdump (int /*<<< orphan*/ *,unsigned int const) ; 
 scalar_t__ is_test_sglist_corrupted (TYPE_2__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int const) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int const) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (struct skcipher_request*,scalar_t__ const,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (struct skcipher_request*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testmgr_poison (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int verify_correct_output (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int test_skcipher_vec_cfg(const char *driver, int enc,
				 const struct cipher_testvec *vec,
				 const char *vec_name,
				 const struct testvec_config *cfg,
				 struct skcipher_request *req,
				 struct cipher_test_sglists *tsgls)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	const unsigned int alignmask = crypto_skcipher_alignmask(tfm);
	const unsigned int ivsize = crypto_skcipher_ivsize(tfm);
	const u32 req_flags = CRYPTO_TFM_REQ_MAY_BACKLOG | cfg->req_flags;
	const char *op = enc ? "encryption" : "decryption";
	DECLARE_CRYPTO_WAIT(wait);
	u8 _iv[3 * (MAX_ALGAPI_ALIGNMASK + 1) + MAX_IVLEN];
	u8 *iv = PTR_ALIGN(&_iv[0], 2 * (MAX_ALGAPI_ALIGNMASK + 1)) +
		 cfg->iv_offset +
		 (cfg->iv_offset_relative_to_alignmask ? alignmask : 0);
	struct kvec input;
	int err;

	/* Set the key */
	if (vec->wk)
		crypto_skcipher_set_flags(tfm, CRYPTO_TFM_REQ_FORBID_WEAK_KEYS);
	else
		crypto_skcipher_clear_flags(tfm,
					    CRYPTO_TFM_REQ_FORBID_WEAK_KEYS);
	err = crypto_skcipher_setkey(tfm, vec->key, vec->klen);
	if (err) {
		if (err == vec->setkey_error)
			return 0;
		pr_err("alg: skcipher: %s setkey failed on test vector %s; expected_error=%d, actual_error=%d, flags=%#x\n",
		       driver, vec_name, vec->setkey_error, err,
		       crypto_skcipher_get_flags(tfm));
		return err;
	}
	if (vec->setkey_error) {
		pr_err("alg: skcipher: %s setkey unexpectedly succeeded on test vector %s; expected_error=%d\n",
		       driver, vec_name, vec->setkey_error);
		return -EINVAL;
	}

	/* The IV must be copied to a buffer, as the algorithm may modify it */
	if (ivsize) {
		if (WARN_ON(ivsize > MAX_IVLEN))
			return -EINVAL;
		if (vec->generates_iv && !enc)
			memcpy(iv, vec->iv_out, ivsize);
		else if (vec->iv)
			memcpy(iv, vec->iv, ivsize);
		else
			memset(iv, 0, ivsize);
	} else {
		if (vec->generates_iv) {
			pr_err("alg: skcipher: %s has ivsize=0 but test vector %s generates IV!\n",
			       driver, vec_name);
			return -EINVAL;
		}
		iv = NULL;
	}

	/* Build the src/dst scatterlists */
	input.iov_base = enc ? (void *)vec->ptext : (void *)vec->ctext;
	input.iov_len = vec->len;
	err = build_cipher_test_sglists(tsgls, cfg, alignmask,
					vec->len, vec->len, &input, 1);
	if (err) {
		pr_err("alg: skcipher: %s %s: error preparing scatterlists for test vector %s, cfg=\"%s\"\n",
		       driver, op, vec_name, cfg->name);
		return err;
	}

	/* Do the actual encryption or decryption */
	testmgr_poison(req->__ctx, crypto_skcipher_reqsize(tfm));
	skcipher_request_set_callback(req, req_flags, crypto_req_done, &wait);
	skcipher_request_set_crypt(req, tsgls->src.sgl_ptr, tsgls->dst.sgl_ptr,
				   vec->len, iv);
	if (cfg->nosimd)
		crypto_disable_simd_for_test();
	err = enc ? crypto_skcipher_encrypt(req) : crypto_skcipher_decrypt(req);
	if (cfg->nosimd)
		crypto_reenable_simd_for_test();
	err = crypto_wait_req(err, &wait);

	/* Check that the algorithm didn't overwrite things it shouldn't have */
	if (req->cryptlen != vec->len ||
	    req->iv != iv ||
	    req->src != tsgls->src.sgl_ptr ||
	    req->dst != tsgls->dst.sgl_ptr ||
	    crypto_skcipher_reqtfm(req) != tfm ||
	    req->base.complete != crypto_req_done ||
	    req->base.flags != req_flags ||
	    req->base.data != &wait) {
		pr_err("alg: skcipher: %s %s corrupted request struct on test vector %s, cfg=\"%s\"\n",
		       driver, op, vec_name, cfg->name);
		if (req->cryptlen != vec->len)
			pr_err("alg: skcipher: changed 'req->cryptlen'\n");
		if (req->iv != iv)
			pr_err("alg: skcipher: changed 'req->iv'\n");
		if (req->src != tsgls->src.sgl_ptr)
			pr_err("alg: skcipher: changed 'req->src'\n");
		if (req->dst != tsgls->dst.sgl_ptr)
			pr_err("alg: skcipher: changed 'req->dst'\n");
		if (crypto_skcipher_reqtfm(req) != tfm)
			pr_err("alg: skcipher: changed 'req->base.tfm'\n");
		if (req->base.complete != crypto_req_done)
			pr_err("alg: skcipher: changed 'req->base.complete'\n");
		if (req->base.flags != req_flags)
			pr_err("alg: skcipher: changed 'req->base.flags'\n");
		if (req->base.data != &wait)
			pr_err("alg: skcipher: changed 'req->base.data'\n");
		return -EINVAL;
	}
	if (is_test_sglist_corrupted(&tsgls->src)) {
		pr_err("alg: skcipher: %s %s corrupted src sgl on test vector %s, cfg=\"%s\"\n",
		       driver, op, vec_name, cfg->name);
		return -EINVAL;
	}
	if (tsgls->dst.sgl_ptr != tsgls->src.sgl &&
	    is_test_sglist_corrupted(&tsgls->dst)) {
		pr_err("alg: skcipher: %s %s corrupted dst sgl on test vector %s, cfg=\"%s\"\n",
		       driver, op, vec_name, cfg->name);
		return -EINVAL;
	}

	/* Check for success or failure */
	if (err) {
		if (err == vec->crypt_error)
			return 0;
		pr_err("alg: skcipher: %s %s failed on test vector %s; expected_error=%d, actual_error=%d, cfg=\"%s\"\n",
		       driver, op, vec_name, vec->crypt_error, err, cfg->name);
		return err;
	}
	if (vec->crypt_error) {
		pr_err("alg: skcipher: %s %s unexpectedly succeeded on test vector %s; expected_error=%d, cfg=\"%s\"\n",
		       driver, op, vec_name, vec->crypt_error, cfg->name);
		return -EINVAL;
	}

	/* Check for the correct output (ciphertext or plaintext) */
	err = verify_correct_output(&tsgls->dst, enc ? vec->ctext : vec->ptext,
				    vec->len, 0, true);
	if (err == -EOVERFLOW) {
		pr_err("alg: skcipher: %s %s overran dst buffer on test vector %s, cfg=\"%s\"\n",
		       driver, op, vec_name, cfg->name);
		return err;
	}
	if (err) {
		pr_err("alg: skcipher: %s %s test failed (wrong result) on test vector %s, cfg=\"%s\"\n",
		       driver, op, vec_name, cfg->name);
		return err;
	}

	/* If applicable, check that the algorithm generated the correct IV */
	if (vec->iv_out && memcmp(iv, vec->iv_out, ivsize) != 0) {
		pr_err("alg: skcipher: %s %s test failed (wrong output IV) on test vector %s, cfg=\"%s\"\n",
		       driver, op, vec_name, cfg->name);
		hexdump(iv, ivsize);
		return -EINVAL;
	}

	return 0;
}