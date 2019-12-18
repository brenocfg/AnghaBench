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
struct scatterlist {int dummy; } ;
struct kpp_testvec {void* expected_a_public; unsigned int expected_a_public_size; unsigned int b_public_size; unsigned int expected_ss_size; scalar_t__ expected_ss; int /*<<< orphan*/  b_secret_size; int /*<<< orphan*/  b_secret; scalar_t__ genkey; int /*<<< orphan*/  b_public; int /*<<< orphan*/  secret_size; int /*<<< orphan*/  secret; } ;
struct kpp_request {int /*<<< orphan*/  dst; } ;
struct crypto_wait {int dummy; } ;
struct crypto_kpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  crypto_init_wait (struct crypto_wait*) ; 
 int /*<<< orphan*/  crypto_kpp_compute_shared_secret (struct kpp_request*) ; 
 int /*<<< orphan*/  crypto_kpp_generate_public_key (struct kpp_request*) ; 
 unsigned int crypto_kpp_maxsize (struct crypto_kpp*) ; 
 int crypto_kpp_set_secret (struct crypto_kpp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_req_done ; 
 int crypto_wait_req (int /*<<< orphan*/ ,struct crypto_wait*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmemdup (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 struct kpp_request* kpp_request_alloc (struct crypto_kpp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kpp_request_free (struct kpp_request*) ; 
 int /*<<< orphan*/  kpp_request_set_callback (struct kpp_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct crypto_wait*) ; 
 int /*<<< orphan*/  kpp_request_set_input (struct kpp_request*,struct scatterlist*,unsigned int) ; 
 int /*<<< orphan*/  kpp_request_set_output (struct kpp_request*,struct scatterlist*,unsigned int) ; 
 void* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (void*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,...) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,void*,unsigned int) ; 
 int /*<<< orphan*/  sg_virt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_test_kpp(struct crypto_kpp *tfm, const struct kpp_testvec *vec,
		       const char *alg)
{
	struct kpp_request *req;
	void *input_buf = NULL;
	void *output_buf = NULL;
	void *a_public = NULL;
	void *a_ss = NULL;
	void *shared_secret = NULL;
	struct crypto_wait wait;
	unsigned int out_len_max;
	int err = -ENOMEM;
	struct scatterlist src, dst;

	req = kpp_request_alloc(tfm, GFP_KERNEL);
	if (!req)
		return err;

	crypto_init_wait(&wait);

	err = crypto_kpp_set_secret(tfm, vec->secret, vec->secret_size);
	if (err < 0)
		goto free_req;

	out_len_max = crypto_kpp_maxsize(tfm);
	output_buf = kzalloc(out_len_max, GFP_KERNEL);
	if (!output_buf) {
		err = -ENOMEM;
		goto free_req;
	}

	/* Use appropriate parameter as base */
	kpp_request_set_input(req, NULL, 0);
	sg_init_one(&dst, output_buf, out_len_max);
	kpp_request_set_output(req, &dst, out_len_max);
	kpp_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				 crypto_req_done, &wait);

	/* Compute party A's public key */
	err = crypto_wait_req(crypto_kpp_generate_public_key(req), &wait);
	if (err) {
		pr_err("alg: %s: Party A: generate public key test failed. err %d\n",
		       alg, err);
		goto free_output;
	}

	if (vec->genkey) {
		/* Save party A's public key */
		a_public = kmemdup(sg_virt(req->dst), out_len_max, GFP_KERNEL);
		if (!a_public) {
			err = -ENOMEM;
			goto free_output;
		}
	} else {
		/* Verify calculated public key */
		if (memcmp(vec->expected_a_public, sg_virt(req->dst),
			   vec->expected_a_public_size)) {
			pr_err("alg: %s: Party A: generate public key test failed. Invalid output\n",
			       alg);
			err = -EINVAL;
			goto free_output;
		}
	}

	/* Calculate shared secret key by using counter part (b) public key. */
	input_buf = kmemdup(vec->b_public, vec->b_public_size, GFP_KERNEL);
	if (!input_buf) {
		err = -ENOMEM;
		goto free_output;
	}

	sg_init_one(&src, input_buf, vec->b_public_size);
	sg_init_one(&dst, output_buf, out_len_max);
	kpp_request_set_input(req, &src, vec->b_public_size);
	kpp_request_set_output(req, &dst, out_len_max);
	kpp_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				 crypto_req_done, &wait);
	err = crypto_wait_req(crypto_kpp_compute_shared_secret(req), &wait);
	if (err) {
		pr_err("alg: %s: Party A: compute shared secret test failed. err %d\n",
		       alg, err);
		goto free_all;
	}

	if (vec->genkey) {
		/* Save the shared secret obtained by party A */
		a_ss = kmemdup(sg_virt(req->dst), vec->expected_ss_size, GFP_KERNEL);
		if (!a_ss) {
			err = -ENOMEM;
			goto free_all;
		}

		/*
		 * Calculate party B's shared secret by using party A's
		 * public key.
		 */
		err = crypto_kpp_set_secret(tfm, vec->b_secret,
					    vec->b_secret_size);
		if (err < 0)
			goto free_all;

		sg_init_one(&src, a_public, vec->expected_a_public_size);
		sg_init_one(&dst, output_buf, out_len_max);
		kpp_request_set_input(req, &src, vec->expected_a_public_size);
		kpp_request_set_output(req, &dst, out_len_max);
		kpp_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
					 crypto_req_done, &wait);
		err = crypto_wait_req(crypto_kpp_compute_shared_secret(req),
				      &wait);
		if (err) {
			pr_err("alg: %s: Party B: compute shared secret failed. err %d\n",
			       alg, err);
			goto free_all;
		}

		shared_secret = a_ss;
	} else {
		shared_secret = (void *)vec->expected_ss;
	}

	/*
	 * verify shared secret from which the user will derive
	 * secret key by executing whatever hash it has chosen
	 */
	if (memcmp(shared_secret, sg_virt(req->dst),
		   vec->expected_ss_size)) {
		pr_err("alg: %s: compute shared secret test failed. Invalid output\n",
		       alg);
		err = -EINVAL;
	}

free_all:
	kfree(a_ss);
	kfree(input_buf);
free_output:
	kfree(a_public);
	kfree(output_buf);
free_req:
	kpp_request_free(req);
	return err;
}