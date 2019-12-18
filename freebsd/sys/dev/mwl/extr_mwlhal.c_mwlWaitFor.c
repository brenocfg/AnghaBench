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
typedef  scalar_t__ uint32_t ;
struct mwl_hal_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_CHECK_USECS ; 
 int FW_MAX_NUM_CHECKS ; 
 int /*<<< orphan*/  MACREG_REG_INT_CODE ; 
 scalar_t__ RD4 (struct mwl_hal_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mwlWaitFor(struct mwl_hal_priv *mh, uint32_t val)
{
	int i;

	for (i = 0; i < FW_MAX_NUM_CHECKS; i++) {
		DELAY(FW_CHECK_USECS);
		if (RD4(mh, MACREG_REG_INT_CODE) == val)
			return 1;
	}
	return 0;
}