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
struct rev_info {int dummy; } ;
struct object_id {int dummy; } ;
struct object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_pending_object (struct rev_info*,struct object*,char const*) ; 
 struct object* get_reference (struct rev_info*,char const*,struct object_id const*,unsigned int) ; 

void add_pending_oid(struct rev_info *revs, const char *name,
		      const struct object_id *oid, unsigned int flags)
{
	struct object *object = get_reference(revs, name, oid, flags);
	add_pending_object(revs, object, name);
}