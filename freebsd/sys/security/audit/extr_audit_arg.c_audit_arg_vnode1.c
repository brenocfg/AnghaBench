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
struct vnode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ar_arg_vnode1; } ;
struct kaudit_record {TYPE_1__ k_ar; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_CLEAR_VALID (struct kaudit_record*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARG_SET_VALID (struct kaudit_record*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARG_VNODE1 ; 
 int audit_arg_vnode (struct vnode*,int /*<<< orphan*/ *) ; 
 struct kaudit_record* currecord () ; 

void
audit_arg_vnode1(struct vnode *vp)
{
	struct kaudit_record *ar;
	int error;

	ar = currecord();
	if (ar == NULL)
		return;

	ARG_CLEAR_VALID(ar, ARG_VNODE1);
	error = audit_arg_vnode(vp, &ar->k_ar.ar_arg_vnode1);
	if (error == 0)
		ARG_SET_VALID(ar, ARG_VNODE1);
}