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
typedef  scalar_t__ u_int ;
struct ath_hal {int dummy; } ;
struct ath_desc {int dummy; } ;
struct ar5416_desc {int /*<<< orphan*/  ds_ctl0; } ;

/* Variables and functions */
 struct ar5416_desc* AR5416DESC (struct ath_desc*) ; 
 int /*<<< orphan*/  AR_VirtMoreFrag ; 

void
ar5416Set11nVirtualMoreFrag(struct ath_hal *ah, struct ath_desc *ds,
    u_int vmf)
{
	struct ar5416_desc *ads = AR5416DESC(ds);
	if (vmf)
		ads->ds_ctl0 |= AR_VirtMoreFrag;
	else
		ads->ds_ctl0 &= ~AR_VirtMoreFrag;
}