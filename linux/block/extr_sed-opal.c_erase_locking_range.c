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
typedef  int /*<<< orphan*/  uid ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  lr; } ;
struct opal_session_info {TYPE_1__ opal_key; } ;
struct opal_dev {int dummy; } ;

/* Variables and functions */
 int ERANGE ; 
 size_t OPAL_ERASE ; 
 int OPAL_UID_LENGTH ; 
 scalar_t__ build_locking_range (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int cmd_start (struct opal_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int finalize_and_send (struct opal_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opalmethod ; 
 int /*<<< orphan*/  parse_and_check_status ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int erase_locking_range(struct opal_dev *dev, void *data)
{
	struct opal_session_info *session = data;
	u8 uid[OPAL_UID_LENGTH];
	int err;

	if (build_locking_range(uid, sizeof(uid), session->opal_key.lr) < 0)
		return -ERANGE;

	err = cmd_start(dev, uid, opalmethod[OPAL_ERASE]);

	if (err) {
		pr_debug("Error building Erase Locking Range Command.\n");
		return err;
	}

	return finalize_and_send(dev, parse_and_check_status);
}