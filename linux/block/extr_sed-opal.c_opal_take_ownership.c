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
 int ENODEV ; 
 int /*<<< orphan*/  end_opal_session ; 
 int execute_steps (struct opal_dev*,struct opal_step const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_msid_cpin_pin ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_sid_cpin_pin ; 
 int /*<<< orphan*/  setup_opal_dev (struct opal_dev*) ; 
 int /*<<< orphan*/  start_SIDASP_opal_session ; 
 int /*<<< orphan*/  start_anybodyASP_opal_session ; 

__attribute__((used)) static int opal_take_ownership(struct opal_dev *dev, struct opal_key *opal)
{
	const struct opal_step owner_steps[] = {
		{ start_anybodyASP_opal_session, },
		{ get_msid_cpin_pin, },
		{ end_opal_session, },
		{ start_SIDASP_opal_session, opal },
		{ set_sid_cpin_pin, opal },
		{ end_opal_session, }
	};
	int ret;

	if (!dev)
		return -ENODEV;

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev);
	ret = execute_steps(dev, owner_steps, ARRAY_SIZE(owner_steps));
	mutex_unlock(&dev->dev_lock);

	return ret;
}