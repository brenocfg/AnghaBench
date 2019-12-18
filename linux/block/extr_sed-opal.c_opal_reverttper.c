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
struct opal_step {int /*<<< orphan*/  member_0; struct opal_key* member_1; } ;
struct opal_key {int dummy; } ;
struct opal_dev {int /*<<< orphan*/  dev_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct opal_step const*) ; 
 int /*<<< orphan*/  clean_opal_dev (struct opal_dev*) ; 
 int execute_steps (struct opal_dev*,struct opal_step const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  revert_tper ; 
 int /*<<< orphan*/  setup_opal_dev (struct opal_dev*) ; 
 int /*<<< orphan*/  start_PSID_opal_session ; 
 int /*<<< orphan*/  start_SIDASP_opal_session ; 

__attribute__((used)) static int opal_reverttper(struct opal_dev *dev, struct opal_key *opal, bool psid)
{
	/* controller will terminate session */
	const struct opal_step revert_steps[] = {
		{ start_SIDASP_opal_session, opal },
		{ revert_tper, }
	};
	const struct opal_step psid_revert_steps[] = {
		{ start_PSID_opal_session, opal },
		{ revert_tper, }
	};

	int ret;

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev);
	if (psid)
		ret = execute_steps(dev, psid_revert_steps,
				    ARRAY_SIZE(psid_revert_steps));
	else
		ret = execute_steps(dev, revert_steps,
				    ARRAY_SIZE(revert_steps));
	mutex_unlock(&dev->dev_lock);

	/*
	 * If we successfully reverted lets clean
	 * any saved locking ranges.
	 */
	if (!ret)
		clean_opal_dev(dev);

	return ret;
}