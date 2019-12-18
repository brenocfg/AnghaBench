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
struct opal_mbr_done {scalar_t__ done_flag; int /*<<< orphan*/  key; } ;
struct opal_dev {int /*<<< orphan*/  dev_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct opal_step const*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  OPAL_FALSE ; 
 scalar_t__ OPAL_MBR_DONE ; 
 scalar_t__ OPAL_MBR_NOT_DONE ; 
 int /*<<< orphan*/  OPAL_TRUE ; 
 int /*<<< orphan*/  end_opal_session ; 
 int execute_steps (struct opal_dev*,struct opal_step const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_mbr_done ; 
 int /*<<< orphan*/  setup_opal_dev (struct opal_dev*) ; 
 int /*<<< orphan*/  start_admin1LSP_opal_session ; 

__attribute__((used)) static int opal_set_mbr_done(struct opal_dev *dev,
			     struct opal_mbr_done *mbr_done)
{
	u8 mbr_done_tf = mbr_done->done_flag == OPAL_MBR_DONE ?
		OPAL_TRUE : OPAL_FALSE;

	const struct opal_step mbr_steps[] = {
		{ start_admin1LSP_opal_session, &mbr_done->key },
		{ set_mbr_done, &mbr_done_tf },
		{ end_opal_session, }
	};
	int ret;

	if (mbr_done->done_flag != OPAL_MBR_DONE &&
	    mbr_done->done_flag != OPAL_MBR_NOT_DONE)
		return -EINVAL;

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev);
	ret = execute_steps(dev, mbr_steps, ARRAY_SIZE(mbr_steps));
	mutex_unlock(&dev->dev_lock);

	return ret;
}