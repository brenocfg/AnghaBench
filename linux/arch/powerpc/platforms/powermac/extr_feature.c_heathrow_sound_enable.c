#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct macio_chip {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {scalar_t__ model_id; } ;

/* Variables and functions */
 long ENODEV ; 
 int /*<<< orphan*/  HEATHROW_FCR ; 
 int /*<<< orphan*/  HRW_SOUND_CLK_ENABLE ; 
 int /*<<< orphan*/  HRW_SOUND_POWER_N ; 
 int /*<<< orphan*/  LOCK (unsigned long) ; 
 int /*<<< orphan*/  MACIO_BIC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACIO_BIS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACIO_IN32 (int /*<<< orphan*/ ) ; 
 scalar_t__ PMAC_TYPE_YIKES ; 
 scalar_t__ PMAC_TYPE_YOSEMITE ; 
 int /*<<< orphan*/  UNLOCK (unsigned long) ; 
 struct macio_chip* macio_find (struct device_node*,int /*<<< orphan*/ ) ; 
 TYPE_1__ pmac_mb ; 

__attribute__((used)) static long heathrow_sound_enable(struct device_node *node, long param,
				  long value)
{
	struct macio_chip*	macio;
	unsigned long		flags;

	/* B&W G3 and Yikes don't support that properly (the
	 * sound appear to never come back after being shut down).
	 */
	if (pmac_mb.model_id == PMAC_TYPE_YOSEMITE ||
	    pmac_mb.model_id == PMAC_TYPE_YIKES)
		return 0;

	macio = macio_find(node, 0);
	if (!macio)
		return -ENODEV;
	if (value) {
		LOCK(flags);
		MACIO_BIS(HEATHROW_FCR, HRW_SOUND_CLK_ENABLE);
		MACIO_BIC(HEATHROW_FCR, HRW_SOUND_POWER_N);
		UNLOCK(flags);
		(void)MACIO_IN32(HEATHROW_FCR);
	} else {
		LOCK(flags);
		MACIO_BIS(HEATHROW_FCR, HRW_SOUND_POWER_N);
		MACIO_BIC(HEATHROW_FCR, HRW_SOUND_CLK_ENABLE);
		UNLOCK(flags);
	}
	return 0;
}