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
typedef  int /*<<< orphan*/  uid ;
typedef  int /*<<< orphan*/  u8 ;
struct opal_dev {int /*<<< orphan*/ * prev_data; int /*<<< orphan*/  prev_d_len; } ;

/* Variables and functions */
 size_t OPAL_GENKEY ; 
 int OPAL_UID_LENGTH ; 
 int cmd_start (struct opal_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int finalize_and_send (struct opal_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opalmethod ; 
 int /*<<< orphan*/  parse_and_check_status ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int gen_key(struct opal_dev *dev, void *data)
{
	u8 uid[OPAL_UID_LENGTH];
	int err;

	memcpy(uid, dev->prev_data, min(sizeof(uid), dev->prev_d_len));
	kfree(dev->prev_data);
	dev->prev_data = NULL;

	err = cmd_start(dev, uid, opalmethod[OPAL_GENKEY]);

	if (err) {
		pr_debug("Error building gen key command\n");
		return err;

	}

	return finalize_and_send(dev, parse_and_check_status);
}