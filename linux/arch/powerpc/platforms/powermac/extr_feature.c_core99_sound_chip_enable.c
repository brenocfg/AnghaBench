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
 int KEYLARGO_GPIO_OUTOUT_DATA ; 
 int KEYLARGO_GPIO_OUTPUT_ENABLE ; 
 int /*<<< orphan*/  KL_GPIO_SOUND_POWER ; 
 int /*<<< orphan*/  LOCK (unsigned long) ; 
 int /*<<< orphan*/  MACIO_IN8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACIO_OUT8 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ PMAC_TYPE_PISMO ; 
 scalar_t__ PMAC_TYPE_TITANIUM ; 
 int /*<<< orphan*/  UNLOCK (unsigned long) ; 
 struct macio_chip* macio_find (struct device_node*,int /*<<< orphan*/ ) ; 
 TYPE_1__ pmac_mb ; 

__attribute__((used)) static long
core99_sound_chip_enable(struct device_node *node, long param, long value)
{
	struct macio_chip*	macio;
	unsigned long		flags;

	macio = macio_find(node, 0);
	if (!macio)
		return -ENODEV;

	/* Do a better probe code, screamer G4 desktops &
	 * iMacs can do that too, add a recalibrate  in
	 * the driver as well
	 */
	if (pmac_mb.model_id == PMAC_TYPE_PISMO ||
	    pmac_mb.model_id == PMAC_TYPE_TITANIUM) {
		LOCK(flags);
		if (value)
			MACIO_OUT8(KL_GPIO_SOUND_POWER,
				KEYLARGO_GPIO_OUTPUT_ENABLE |
				KEYLARGO_GPIO_OUTOUT_DATA);
		else
			MACIO_OUT8(KL_GPIO_SOUND_POWER,
				KEYLARGO_GPIO_OUTPUT_ENABLE);
		(void)MACIO_IN8(KL_GPIO_SOUND_POWER);
		UNLOCK(flags);
	}
	return 0;
}