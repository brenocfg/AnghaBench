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
typedef  int /*<<< orphan*/  u8 ;
struct opal_step {int /*<<< orphan*/  member_0; int /*<<< orphan*/ * member_1; } ;
struct opal_mbr_data {scalar_t__ enable_disable; int /*<<< orphan*/  key; } ;
struct opal_dev {int /*<<< orphan*/  dev_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct opal_step const*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  OPAL_FALSE ; 
 scalar_t__ OPAL_MBR_DISABLE ; 
 scalar_t__ OPAL_MBR_ENABLE ; 
 int /*<<< orphan*/  OPAL_TRUE ; 
 int /*<<< orphan*/  end_opal_session ; 
 int execute_steps (struct opal_dev*,struct opal_step const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_mbr_done ; 
 int /*<<< orphan*/  set_mbr_enable_disable ; 
 int /*<<< orphan*/  setup_opal_dev (struct opal_dev*) ; 
 int /*<<< orphan*/  start_admin1LSP_opal_session ; 

__attribute__((used)) static int opal_enable_disable_shadow_mbr(struct opal_dev *dev,
					  struct opal_mbr_data *opal_mbr)
{
	u8 enable_disable = opal_mbr->enable_disable == OPAL_MBR_ENABLE ?
		OPAL_TRUE : OPAL_FALSE;

	const struct opal_step mbr_steps[] = {
		{ start_admin1LSP_opal_session, &opal_mbr->key },
		{ set_mbr_done, &enable_disable },
		{ end_opal_session, },
		{ start_admin1LSP_opal_session, &opal_mbr->key },
		{ set_mbr_enable_disable, &enable_disable },
		{ end_opal_session, }
	};
	int ret;

	if (opal_mbr->enable_disable != OPAL_MBR_ENABLE &&
	    opal_mbr->enable_disable != OPAL_MBR_DISABLE)
		return -EINVAL;

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev);
	ret = execute_steps(dev, mbr_steps, ARRAY_SIZE(mbr_steps));
	mutex_unlock(&dev->dev_lock);

	return ret;
}