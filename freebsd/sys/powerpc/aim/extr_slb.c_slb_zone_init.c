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
struct slbtnode {int dummy; } ;
struct slb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int /*<<< orphan*/  UMA_ZONE_VM ; 
 scalar_t__ VM_MAX_ADDRESS ; 
 int n_slbs ; 
 scalar_t__ platform_real_maxaddr () ; 
 int /*<<< orphan*/  slb_cache_zone ; 
 int /*<<< orphan*/  slb_uma_real_alloc ; 
 int /*<<< orphan*/  slbt_zone ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zone_set_allocf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
slb_zone_init(void *dummy)
{

	slbt_zone = uma_zcreate("SLB tree node", sizeof(struct slbtnode),
	    NULL, NULL, NULL, NULL, UMA_ALIGN_PTR, UMA_ZONE_VM);
	slb_cache_zone = uma_zcreate("SLB cache",
	    (n_slbs + 1)*sizeof(struct slb *), NULL, NULL, NULL, NULL,
	    UMA_ALIGN_PTR, UMA_ZONE_VM);

	if (platform_real_maxaddr() != VM_MAX_ADDRESS) {
		uma_zone_set_allocf(slb_cache_zone, slb_uma_real_alloc);
		uma_zone_set_allocf(slbt_zone, slb_uma_real_alloc);
	}
}