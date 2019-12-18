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
typedef  scalar_t__ u8 ;
struct opal_dev {int /*<<< orphan*/  parsed; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  OPAL_LIFECYCLE ; 
 size_t OPAL_LOCKINGSP_UID ; 
 scalar_t__ OPAL_MANUFACTURED_INACTIVE ; 
 int generic_get_column (struct opal_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opaluid ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 scalar_t__ response_get_u64 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int get_lsp_lifecycle(struct opal_dev *dev, void *data)
{
	u8 lc_status;
	int err;

	err = generic_get_column(dev, opaluid[OPAL_LOCKINGSP_UID],
				 OPAL_LIFECYCLE);
	if (err)
		return err;

	lc_status = response_get_u64(&dev->parsed, 4);
	/* 0x08 is Manufactured Inactive */
	/* 0x09 is Manufactured */
	if (lc_status != OPAL_MANUFACTURED_INACTIVE) {
		pr_debug("Couldn't determine the status of the Lifecycle state\n");
		return -ENODEV;
	}

	return 0;
}