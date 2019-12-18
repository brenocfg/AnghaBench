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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum mbox_cmd { ____Placeholder_mbox_cmd } mbox_cmd ;

/* Variables and functions */
 int EIO ; 
 int MBOX_STS_CMD (int /*<<< orphan*/ ) ; 
 scalar_t__ MBOX_STS_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ MBOX_STS_FAIL ; 
 scalar_t__ MBOX_STS_SUCCESS ; 
 int MBOX_STS_VALUE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mox_get_status(enum mbox_cmd cmd, u32 retval)
{
	if (MBOX_STS_CMD(retval) != cmd ||
	    MBOX_STS_ERROR(retval) != MBOX_STS_SUCCESS)
		return -EIO;
	else if (MBOX_STS_ERROR(retval) == MBOX_STS_FAIL)
		return -(int)MBOX_STS_VALUE(retval);
	else
		return MBOX_STS_VALUE(retval);
}