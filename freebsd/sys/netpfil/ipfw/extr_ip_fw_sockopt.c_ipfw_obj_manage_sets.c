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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct namedobj_instance {int dummy; } ;
struct named_object {void* set; int /*<<< orphan*/  name; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  ocnt; } ;
struct manage_sets_args {void* new_set; int /*<<< orphan*/  set; } ;
typedef  enum ipfw_sets_cmd { ____Placeholder_ipfw_sets_cmd } ipfw_sets_cmd ;

/* Variables and functions */
#define  COUNT_ONE 133 
 int EBUSY ; 
 int EEXIST ; 
 int EINVAL ; 
#define  MOVE_ALL 132 
#define  MOVE_ONE 131 
#define  SWAP_ALL 130 
#define  TEST_ALL 129 
#define  TEST_ONE 128 
 int ipfw_objhash_foreach_type (struct namedobj_instance*,int /*<<< orphan*/ ,struct manage_sets_args*,int /*<<< orphan*/ ) ; 
 struct named_object* ipfw_objhash_lookup_kidx (struct namedobj_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ipfw_objhash_lookup_name_type (struct namedobj_instance*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  move_sets_cb ; 
 int /*<<< orphan*/  swap_sets_cb ; 
 int /*<<< orphan*/  test_sets_cb ; 

int
ipfw_obj_manage_sets(struct namedobj_instance *ni, uint16_t type,
    uint16_t set, uint8_t new_set, enum ipfw_sets_cmd cmd)
{
	struct manage_sets_args args;
	struct named_object *no;

	args.set = set;
	args.new_set = new_set;
	switch (cmd) {
	case SWAP_ALL:
		return (ipfw_objhash_foreach_type(ni, swap_sets_cb,
		    &args, type));
	case TEST_ALL:
		return (ipfw_objhash_foreach_type(ni, test_sets_cb,
		    &args, type));
	case MOVE_ALL:
		return (ipfw_objhash_foreach_type(ni, move_sets_cb,
		    &args, type));
	case COUNT_ONE:
		/*
		 * @set used to pass kidx.
		 * When @new_set is zero - reset object counter,
		 * otherwise increment it.
		 */
		no = ipfw_objhash_lookup_kidx(ni, set);
		if (new_set != 0)
			no->ocnt++;
		else
			no->ocnt = 0;
		return (0);
	case TEST_ONE:
		/* @set used to pass kidx */
		no = ipfw_objhash_lookup_kidx(ni, set);
		/*
		 * First check number of references:
		 * when it differs, this mean other rules are holding
		 * reference to given object, so it is not possible to
		 * change its set. Note that refcnt may account references
		 * to some going-to-be-added rules. Since we don't know
		 * their numbers (and even if they will be added) it is
		 * perfectly OK to return error here.
		 */
		if (no->ocnt != no->refcnt)
			return (EBUSY);
		if (ipfw_objhash_lookup_name_type(ni, new_set, type,
		    no->name) != NULL)
			return (EEXIST);
		return (0);
	case MOVE_ONE:
		/* @set used to pass kidx */
		no = ipfw_objhash_lookup_kidx(ni, set);
		no->set = new_set;
		return (0);
	}
	return (EINVAL);
}