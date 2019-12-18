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
typedef  int uint32_t ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  mask ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_DIAG_CHECK_HANGS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  ath_hal_getdiagstate (struct ath_hal*,int /*<<< orphan*/ ,int*,int,void**,int*) ; 

int
ath_hal_gethangstate(struct ath_hal *ah, uint32_t mask, uint32_t *hangs)
{
	uint32_t rsize;
	void *sp;

	if (!ath_hal_getdiagstate(ah, HAL_DIAG_CHECK_HANGS, &mask, sizeof(mask), &sp, &rsize))
		return 0;
	KASSERT(rsize == sizeof(uint32_t), ("resultsize %u", rsize));
	*hangs = *(uint32_t *)sp;
	return 1;
}