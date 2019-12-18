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
struct opal_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_ACTIVEKEY ; 
 int OPAL_UID_LENGTH ; 
 int build_locking_range (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int generic_get_column (struct opal_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int get_active_key_cont (struct opal_dev*) ; 

__attribute__((used)) static int get_active_key(struct opal_dev *dev, void *data)
{
	u8 uid[OPAL_UID_LENGTH];
	int err;
	u8 *lr = data;

	err = build_locking_range(uid, sizeof(uid), *lr);
	if (err)
		return err;

	err = generic_get_column(dev, uid, OPAL_ACTIVEKEY);
	if (err)
		return err;

	return get_active_key_cont(dev);
}