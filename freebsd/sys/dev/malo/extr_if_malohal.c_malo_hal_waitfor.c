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
struct malo_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MALO_FW_CHECK_USECS ; 
 int MALO_FW_MAX_NUM_CHECKS ; 
 int /*<<< orphan*/  MALO_REG_INT_CODE ; 
 scalar_t__ malo_hal_read4 (struct malo_hal*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
malo_hal_waitfor(struct malo_hal *mh, uint32_t val)
{
	int i;

	for (i = 0; i < MALO_FW_MAX_NUM_CHECKS; i++) {
		DELAY(MALO_FW_CHECK_USECS);
		if (malo_hal_read4(mh, MALO_REG_INT_CODE) == val)
			return 0;
	}

	return -1;
}