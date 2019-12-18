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
struct opal_step {int /*<<< orphan*/  member_0; struct opal_session_info* member_1; } ;
struct opal_session_info {int dummy; } ;
struct opal_dev {int /*<<< orphan*/  dev_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct opal_step const*) ; 
 int /*<<< orphan*/  end_opal_session ; 
 int /*<<< orphan*/  erase_locking_range ; 
 int execute_steps (struct opal_dev*,struct opal_step const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_opal_dev (struct opal_dev*) ; 
 int /*<<< orphan*/  start_auth_opal_session ; 

__attribute__((used)) static int opal_erase_locking_range(struct opal_dev *dev,
				    struct opal_session_info *opal_session)
{
	const struct opal_step erase_steps[] = {
		{ start_auth_opal_session, opal_session },
		{ erase_locking_range, opal_session },
		{ end_opal_session, }
	};
	int ret;

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev);
	ret = execute_steps(dev, erase_steps, ARRAY_SIZE(erase_steps));
	mutex_unlock(&dev->dev_lock);

	return ret;
}