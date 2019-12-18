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
typedef  int u8 ;
struct macio_chip {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {scalar_t__ model_id; } ;

/* Variables and functions */
 long ENODEV ; 
 int /*<<< orphan*/  HEATHROW_FCR ; 
 int /*<<< orphan*/  HRW_GPIO_MODEM_RESET ; 
 int /*<<< orphan*/  HRW_SCC_TRANS_EN_N ; 
 int /*<<< orphan*/  LOCK (unsigned long) ; 
 int /*<<< orphan*/  MACIO_BIC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACIO_BIS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACIO_IN32 (int /*<<< orphan*/ ) ; 
 int MACIO_IN8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACIO_OUT8 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ PMAC_TYPE_YIKES ; 
 scalar_t__ PMAC_TYPE_YOSEMITE ; 
 int /*<<< orphan*/  UNLOCK (unsigned long) ; 
 struct macio_chip* macio_find (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macio_unknown ; 
 int /*<<< orphan*/  mdelay (int) ; 
 TYPE_1__ pmac_mb ; 

__attribute__((used)) static long heathrow_modem_enable(struct device_node *node, long param,
				  long value)
{
	struct macio_chip*	macio;
	u8			gpio;
	unsigned long		flags;

	macio = macio_find(node, macio_unknown);
	if (!macio)
		return -ENODEV;
	gpio = MACIO_IN8(HRW_GPIO_MODEM_RESET) & ~1;
	if (!value) {
		LOCK(flags);
		MACIO_OUT8(HRW_GPIO_MODEM_RESET, gpio);
		UNLOCK(flags);
		(void)MACIO_IN8(HRW_GPIO_MODEM_RESET);
		mdelay(250);
	}
	if (pmac_mb.model_id != PMAC_TYPE_YOSEMITE &&
	    pmac_mb.model_id != PMAC_TYPE_YIKES) {
		LOCK(flags);
		if (value)
			MACIO_BIC(HEATHROW_FCR, HRW_SCC_TRANS_EN_N);
		else
			MACIO_BIS(HEATHROW_FCR, HRW_SCC_TRANS_EN_N);
		UNLOCK(flags);
		(void)MACIO_IN32(HEATHROW_FCR);
		mdelay(250);
	}
	if (value) {
		LOCK(flags);
		MACIO_OUT8(HRW_GPIO_MODEM_RESET, gpio | 1);
		(void)MACIO_IN8(HRW_GPIO_MODEM_RESET);
		UNLOCK(flags); mdelay(250); LOCK(flags);
		MACIO_OUT8(HRW_GPIO_MODEM_RESET, gpio);
		(void)MACIO_IN8(HRW_GPIO_MODEM_RESET);
		UNLOCK(flags); mdelay(250); LOCK(flags);
		MACIO_OUT8(HRW_GPIO_MODEM_RESET, gpio | 1);
		(void)MACIO_IN8(HRW_GPIO_MODEM_RESET);
		UNLOCK(flags); mdelay(250);
	}
	return 0;
}