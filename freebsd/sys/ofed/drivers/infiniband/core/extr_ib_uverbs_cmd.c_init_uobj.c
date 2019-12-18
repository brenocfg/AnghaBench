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
typedef  int /*<<< orphan*/  u64 ;
struct uverbs_lock_class {int dummy; } ;
struct ib_uobject {scalar_t__ live; int /*<<< orphan*/  mutex; int /*<<< orphan*/  ref; struct ib_ucontext* context; int /*<<< orphan*/  user_handle; } ;
struct ib_ucontext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_uobj(struct ib_uobject *uobj, u64 user_handle,
		      struct ib_ucontext *context, struct uverbs_lock_class *c)
{
	uobj->user_handle = user_handle;
	uobj->context     = context;
	kref_init(&uobj->ref);
	init_rwsem(&uobj->mutex);
	uobj->live        = 0;
}