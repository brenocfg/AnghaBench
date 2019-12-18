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
typedef  char u8 ;
struct prno_parm {int dummy; } ;
struct prng_parm {scalar_t__ parm_block; } ;
typedef  int /*<<< orphan*/  seed ;
typedef  int /*<<< orphan*/  random ;
typedef  int /*<<< orphan*/  entropy ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  CPACF_KMC_PRNG ; 
 int /*<<< orphan*/  CPACF_PRNO_SHA512_DRNG_GEN ; 
 int /*<<< orphan*/  CPACF_PRNO_SHA512_DRNG_SEED ; 
#define  PRNG_MODE_SHA512 130 
#define  PRNG_MODE_TDES 129 
#define  PRNG_MODE_TRNG 128 
 int check_prng () ; 
 int /*<<< orphan*/  cpacf_kmc (int /*<<< orphan*/ ,scalar_t__,char*,char*,int) ; 
 int /*<<< orphan*/  cpacf_prno (int /*<<< orphan*/ ,struct prno_parm*,char*,int,char*,int) ; 
 int /*<<< orphan*/  cpacf_trng (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 unsigned long get_tod_clock_fast () ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static unsigned long get_random(unsigned long limit)
{
	struct prng_parm prng = {
		/* initial parameter block for tdes mode, copied from libica */
		.parm_block = {
			0x0F, 0x2B, 0x8E, 0x63, 0x8C, 0x8E, 0xD2, 0x52,
			0x64, 0xB7, 0xA0, 0x7B, 0x75, 0x28, 0xB8, 0xF4,
			0x75, 0x5F, 0xD2, 0xA6, 0x8D, 0x97, 0x11, 0xFF,
			0x49, 0xD8, 0x23, 0xF3, 0x7E, 0x21, 0xEC, 0xA0
		},
	};
	unsigned long seed, random;
	struct prno_parm prno;
	__u64 entropy[4];
	int mode, i;

	mode = check_prng();
	seed = get_tod_clock_fast();
	switch (mode) {
	case PRNG_MODE_TRNG:
		cpacf_trng(NULL, 0, (u8 *) &random, sizeof(random));
		break;
	case PRNG_MODE_SHA512:
		cpacf_prno(CPACF_PRNO_SHA512_DRNG_SEED, &prno, NULL, 0,
			   (u8 *) &seed, sizeof(seed));
		cpacf_prno(CPACF_PRNO_SHA512_DRNG_GEN, &prno, (u8 *) &random,
			   sizeof(random), NULL, 0);
		break;
	case PRNG_MODE_TDES:
		/* add entropy */
		*(unsigned long *) prng.parm_block ^= seed;
		for (i = 0; i < 16; i++) {
			cpacf_kmc(CPACF_KMC_PRNG, prng.parm_block,
				  (char *) entropy, (char *) entropy,
				  sizeof(entropy));
			memcpy(prng.parm_block, entropy, sizeof(entropy));
		}
		random = seed;
		cpacf_kmc(CPACF_KMC_PRNG, prng.parm_block, (u8 *) &random,
			  (u8 *) &random, sizeof(random));
		break;
	default:
		random = 0;
	}
	return random % limit;
}