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
typedef  int /*<<< orphan*/  entropy ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_3__ {int /*<<< orphan*/  parm_block; } ;
struct TYPE_4__ {TYPE_1__ prngws; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPACF_KMC_PRNG ; 
 int /*<<< orphan*/  cpacf_kmc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* prng_data ; 

__attribute__((used)) static void prng_tdes_add_entropy(void)
{
	__u64 entropy[4];
	unsigned int i;

	for (i = 0; i < 16; i++) {
		cpacf_kmc(CPACF_KMC_PRNG, prng_data->prngws.parm_block,
			  (char *) entropy, (char *) entropy,
			  sizeof(entropy));
		memcpy(prng_data->prngws.parm_block, entropy, sizeof(entropy));
	}
}