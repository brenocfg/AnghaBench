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
struct drbg_string {scalar_t__ len; int /*<<< orphan*/  list; scalar_t__ buf; } ;
struct TYPE_4__ {unsigned char* buf; unsigned int len; int /*<<< orphan*/  list; } ;
struct drbg_state {int /*<<< orphan*/  C; int /*<<< orphan*/  V; int /*<<< orphan*/  jent; TYPE_2__ test_data; TYPE_1__* core; } ;
typedef  int /*<<< orphan*/  entropy ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int __drbg_seed (struct drbg_state*,int /*<<< orphan*/ *,int) ; 
 int crypto_rng_get_bytes (int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 
 int drbg_get_random_bytes (struct drbg_state*,unsigned char*,unsigned int) ; 
 scalar_t__ drbg_max_addtl (struct drbg_state*) ; 
 unsigned int drbg_sec_strength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbg_statelen (struct drbg_state*) ; 
 int /*<<< orphan*/  drbg_string_fill (struct drbg_string*,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memzero_explicit (unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  pr_devel (char*,...) ; 
 int /*<<< orphan*/  seedlist ; 

__attribute__((used)) static int drbg_seed(struct drbg_state *drbg, struct drbg_string *pers,
		     bool reseed)
{
	int ret;
	unsigned char entropy[((32 + 16) * 2)];
	unsigned int entropylen = drbg_sec_strength(drbg->core->flags);
	struct drbg_string data1;
	LIST_HEAD(seedlist);

	/* 9.1 / 9.2 / 9.3.1 step 3 */
	if (pers && pers->len > (drbg_max_addtl(drbg))) {
		pr_devel("DRBG: personalization string too long %zu\n",
			 pers->len);
		return -EINVAL;
	}

	if (list_empty(&drbg->test_data.list)) {
		drbg_string_fill(&data1, drbg->test_data.buf,
				 drbg->test_data.len);
		pr_devel("DRBG: using test entropy\n");
	} else {
		/*
		 * Gather entropy equal to the security strength of the DRBG.
		 * With a derivation function, a nonce is required in addition
		 * to the entropy. A nonce must be at least 1/2 of the security
		 * strength of the DRBG in size. Thus, entropy + nonce is 3/2
		 * of the strength. The consideration of a nonce is only
		 * applicable during initial seeding.
		 */
		BUG_ON(!entropylen);
		if (!reseed)
			entropylen = ((entropylen + 1) / 2) * 3;
		BUG_ON((entropylen * 2) > sizeof(entropy));

		/* Get seed from in-kernel /dev/urandom */
		ret = drbg_get_random_bytes(drbg, entropy, entropylen);
		if (ret)
			goto out;

		if (!drbg->jent) {
			drbg_string_fill(&data1, entropy, entropylen);
			pr_devel("DRBG: (re)seeding with %u bytes of entropy\n",
				 entropylen);
		} else {
			/* Get seed from Jitter RNG */
			ret = crypto_rng_get_bytes(drbg->jent,
						   entropy + entropylen,
						   entropylen);
			if (ret) {
				pr_devel("DRBG: jent failed with %d\n", ret);
				goto out;
			}

			drbg_string_fill(&data1, entropy, entropylen * 2);
			pr_devel("DRBG: (re)seeding with %u bytes of entropy\n",
				 entropylen * 2);
		}
	}
	list_add_tail(&data1.list, &seedlist);

	/*
	 * concatenation of entropy with personalization str / addtl input)
	 * the variable pers is directly handed in by the caller, so check its
	 * contents whether it is appropriate
	 */
	if (pers && pers->buf && 0 < pers->len) {
		list_add_tail(&pers->list, &seedlist);
		pr_devel("DRBG: using personalization string\n");
	}

	if (!reseed) {
		memset(drbg->V, 0, drbg_statelen(drbg));
		memset(drbg->C, 0, drbg_statelen(drbg));
	}

	ret = __drbg_seed(drbg, &seedlist, reseed);

out:
	memzero_explicit(entropy, entropylen * 2);

	return ret;
}