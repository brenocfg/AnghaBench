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
typedef  scalar_t__ uint8_t ;
struct namedobj_instance {int dummy; } ;
struct named_object {scalar_t__ set; int /*<<< orphan*/  name; int /*<<< orphan*/  etlv; } ;
struct manage_sets_args {int /*<<< orphan*/  new_set; scalar_t__ set; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/ * ipfw_objhash_lookup_name_type (struct namedobj_instance*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
test_sets_cb(struct namedobj_instance *ni, struct named_object *no,
    void *arg)
{
	struct manage_sets_args *args;

	args = (struct manage_sets_args *)arg;
	if (no->set != (uint8_t)args->set)
		return (0);
	if (ipfw_objhash_lookup_name_type(ni, args->new_set,
	    no->etlv, no->name) != NULL)
		return (EEXIST);
	return (0);
}