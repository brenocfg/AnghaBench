#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drbg_string {int /*<<< orphan*/  list; int /*<<< orphan*/  len; int /*<<< orphan*/ * buf; } ;
struct drbg_state {int reseed_threshold; int reseed_ctr; int seeded; TYPE_2__* core; TYPE_1__* d_ops; scalar_t__ pr; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {int (* generate ) (struct drbg_state*,unsigned char*,unsigned int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int DRBG_CTR ; 
 int DRBG_HMAC ; 
 int EINVAL ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addtllist ; 
 int alg_test (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbg_max_addtl (struct drbg_state*) ; 
 unsigned int drbg_max_request_bytes (struct drbg_state*) ; 
 int drbg_seed (struct drbg_state*,struct drbg_string*,int) ; 
 int /*<<< orphan*/  drbg_uninstantiate (struct drbg_state*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_devel (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int stub1 (struct drbg_state*,unsigned char*,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drbg_generate(struct drbg_state *drbg,
			 unsigned char *buf, unsigned int buflen,
			 struct drbg_string *addtl)
{
	int len = 0;
	LIST_HEAD(addtllist);

	if (!drbg->core) {
		pr_devel("DRBG: not yet seeded\n");
		return -EINVAL;
	}
	if (0 == buflen || !buf) {
		pr_devel("DRBG: no output buffer provided\n");
		return -EINVAL;
	}
	if (addtl && NULL == addtl->buf && 0 < addtl->len) {
		pr_devel("DRBG: wrong format of additional information\n");
		return -EINVAL;
	}

	/* 9.3.1 step 2 */
	len = -EINVAL;
	if (buflen > (drbg_max_request_bytes(drbg))) {
		pr_devel("DRBG: requested random numbers too large %u\n",
			 buflen);
		goto err;
	}

	/* 9.3.1 step 3 is implicit with the chosen DRBG */

	/* 9.3.1 step 4 */
	if (addtl && addtl->len > (drbg_max_addtl(drbg))) {
		pr_devel("DRBG: additional information string too long %zu\n",
			 addtl->len);
		goto err;
	}
	/* 9.3.1 step 5 is implicit with the chosen DRBG */

	/*
	 * 9.3.1 step 6 and 9 supplemented by 9.3.2 step c is implemented
	 * here. The spec is a bit convoluted here, we make it simpler.
	 */
	if (drbg->reseed_threshold < drbg->reseed_ctr)
		drbg->seeded = false;

	if (drbg->pr || !drbg->seeded) {
		pr_devel("DRBG: reseeding before generation (prediction "
			 "resistance: %s, state %s)\n",
			 drbg->pr ? "true" : "false",
			 drbg->seeded ? "seeded" : "unseeded");
		/* 9.3.1 steps 7.1 through 7.3 */
		len = drbg_seed(drbg, addtl, true);
		if (len)
			goto err;
		/* 9.3.1 step 7.4 */
		addtl = NULL;
	}

	if (addtl && 0 < addtl->len)
		list_add_tail(&addtl->list, &addtllist);
	/* 9.3.1 step 8 and 10 */
	len = drbg->d_ops->generate(drbg, buf, buflen, &addtllist);

	/* 10.1.1.4 step 6, 10.1.2.5 step 7, 10.2.1.5.2 step 7 */
	drbg->reseed_ctr++;
	if (0 >= len)
		goto err;

	/*
	 * Section 11.3.3 requires to re-perform self tests after some
	 * generated random numbers. The chosen value after which self
	 * test is performed is arbitrary, but it should be reasonable.
	 * However, we do not perform the self tests because of the following
	 * reasons: it is mathematically impossible that the initial self tests
	 * were successfully and the following are not. If the initial would
	 * pass and the following would not, the kernel integrity is violated.
	 * In this case, the entire kernel operation is questionable and it
	 * is unlikely that the integrity violation only affects the
	 * correct operation of the DRBG.
	 *
	 * Albeit the following code is commented out, it is provided in
	 * case somebody has a need to implement the test of 11.3.3.
	 */
#if 0
	if (drbg->reseed_ctr && !(drbg->reseed_ctr % 4096)) {
		int err = 0;
		pr_devel("DRBG: start to perform self test\n");
		if (drbg->core->flags & DRBG_HMAC)
			err = alg_test("drbg_pr_hmac_sha256",
				       "drbg_pr_hmac_sha256", 0, 0);
		else if (drbg->core->flags & DRBG_CTR)
			err = alg_test("drbg_pr_ctr_aes128",
				       "drbg_pr_ctr_aes128", 0, 0);
		else
			err = alg_test("drbg_pr_sha256",
				       "drbg_pr_sha256", 0, 0);
		if (err) {
			pr_err("DRBG: periodical self test failed\n");
			/*
			 * uninstantiate implies that from now on, only errors
			 * are returned when reusing this DRBG cipher handle
			 */
			drbg_uninstantiate(drbg);
			return 0;
		} else {
			pr_devel("DRBG: self test successful\n");
		}
	}
#endif

	/*
	 * All operations were successful, return 0 as mandated by
	 * the kernel crypto API interface.
	 */
	len = 0;
err:
	return len;
}