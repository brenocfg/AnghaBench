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
struct mca_config {scalar_t__ monarch_timeout; } ;
struct cpuinfo_x86 {int x86; int x86_model; int x86_stepping; } ;

/* Variables and functions */
 scalar_t__ USEC_PER_SEC ; 
 struct mca_config mca_cfg ; 

__attribute__((used)) static void mce_centaur_feature_init(struct cpuinfo_x86 *c)
{
	struct mca_config *cfg = &mca_cfg;

	 /*
	  * All newer Centaur CPUs support MCE broadcasting. Enable
	  * synchronization with a one second timeout.
	  */
	if ((c->x86 == 6 && c->x86_model == 0xf && c->x86_stepping >= 0xe) ||
	     c->x86 > 6) {
		if (cfg->monarch_timeout < 0)
			cfg->monarch_timeout = USEC_PER_SEC;
	}
}