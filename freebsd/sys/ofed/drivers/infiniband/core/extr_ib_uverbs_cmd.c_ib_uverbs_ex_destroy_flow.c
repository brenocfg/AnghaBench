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
struct ib_uverbs_file {int /*<<< orphan*/  mutex; int /*<<< orphan*/  ucontext; } ;
struct ib_uverbs_destroy_flow {int /*<<< orphan*/  flow_handle; scalar_t__ comp_mask; } ;
struct ib_uobject {int /*<<< orphan*/  list; scalar_t__ live; struct ib_flow* object; } ;
struct ib_udata {int inlen; } ;
struct ib_flow {int dummy; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int EINVAL ; 
 int ib_copy_from_udata (struct ib_uverbs_destroy_flow*,struct ib_udata*,int) ; 
 int ib_destroy_flow (struct ib_flow*) ; 
 int /*<<< orphan*/  ib_uverbs_rule_idr ; 
 int /*<<< orphan*/  idr_remove_uobj (int /*<<< orphan*/ *,struct ib_uobject*) ; 
 struct ib_uobject* idr_write_uobj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_uobj (struct ib_uobject*) ; 
 int /*<<< orphan*/  put_uobj_write (struct ib_uobject*) ; 

int ib_uverbs_ex_destroy_flow(struct ib_uverbs_file *file,
			      struct ib_device *ib_dev,
			      struct ib_udata *ucore,
			      struct ib_udata *uhw)
{
	struct ib_uverbs_destroy_flow	cmd;
	struct ib_flow			*flow_id;
	struct ib_uobject		*uobj;
	int				ret;

	if (ucore->inlen < sizeof(cmd))
		return -EINVAL;

	ret = ib_copy_from_udata(&cmd, ucore, sizeof(cmd));
	if (ret)
		return ret;

	if (cmd.comp_mask)
		return -EINVAL;

	uobj = idr_write_uobj(&ib_uverbs_rule_idr, cmd.flow_handle,
			      file->ucontext);
	if (!uobj)
		return -EINVAL;
	flow_id = uobj->object;

	ret = ib_destroy_flow(flow_id);
	if (!ret)
		uobj->live = 0;

	put_uobj_write(uobj);

	idr_remove_uobj(&ib_uverbs_rule_idr, uobj);

	mutex_lock(&file->mutex);
	list_del(&uobj->list);
	mutex_unlock(&file->mutex);

	put_uobj(uobj);

	return ret;
}