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
struct TYPE_4__ {int /*<<< orphan*/  list; } ;
struct drbg_state {int fips_primed; int /*<<< orphan*/  prev; TYPE_2__ test_data; TYPE_1__* core; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CRYPTO_FIPS ; 
 int EAGAIN ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 unsigned short drbg_sec_strength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fips_enabled ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int memcmp (int /*<<< orphan*/ ,unsigned char const*,unsigned short) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,unsigned short) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int drbg_fips_continuous_test(struct drbg_state *drbg,
				     const unsigned char *entropy)
{
	unsigned short entropylen = drbg_sec_strength(drbg->core->flags);
	int ret = 0;

	if (!IS_ENABLED(CONFIG_CRYPTO_FIPS))
		return 0;

	/* skip test if we test the overall system */
	if (list_empty(&drbg->test_data.list))
		return 0;
	/* only perform test in FIPS mode */
	if (!fips_enabled)
		return 0;

	if (!drbg->fips_primed) {
		/* Priming of FIPS test */
		memcpy(drbg->prev, entropy, entropylen);
		drbg->fips_primed = true;
		/* priming: another round is needed */
		return -EAGAIN;
	}
	ret = memcmp(drbg->prev, entropy, entropylen);
	if (!ret)
		panic("DRBG continuous self test failed\n");
	memcpy(drbg->prev, entropy, entropylen);

	/* the test shall pass when the two values are not equal */
	return 0;
}