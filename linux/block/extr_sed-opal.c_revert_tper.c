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
struct opal_dev {int dummy; } ;

/* Variables and functions */
 size_t OPAL_ADMINSP_UID ; 
 size_t OPAL_REVERT ; 
 int cmd_start (struct opal_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int finalize_and_send (struct opal_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opalmethod ; 
 int /*<<< orphan*/ * opaluid ; 
 int /*<<< orphan*/  parse_and_check_status ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int revert_tper(struct opal_dev *dev, void *data)
{
	int err;

	err = cmd_start(dev, opaluid[OPAL_ADMINSP_UID],
			opalmethod[OPAL_REVERT]);
	if (err) {
		pr_debug("Error building REVERT TPER command.\n");
		return err;
	}

	return finalize_and_send(dev, parse_and_check_status);
}