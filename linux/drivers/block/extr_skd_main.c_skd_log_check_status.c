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
typedef  scalar_t__ u8 ;
struct skd_device {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void skd_log_check_status(struct skd_device *skdev, u8 status, u8 key,
				 u8 code, u8 qual, u8 fruc)
{
	/* If the check condition is of special interest, log a message */
	if ((status == SAM_STAT_CHECK_CONDITION) && (key == 0x02)
	    && (code == 0x04) && (qual == 0x06)) {
		dev_err(&skdev->pdev->dev,
			"*** LOST_WRITE_DATA ERROR *** key/asc/ascq/fruc %02x/%02x/%02x/%02x\n",
			key, code, qual, fruc);
	}
}