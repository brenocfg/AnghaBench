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
struct tag {struct object* tagged; } ;
struct object {scalar_t__ type; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 scalar_t__ OBJ_TAG ; 
 struct object* parse_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_repository ; 

struct object *deref_tag_noverify(struct object *o)
{
	while (o && o->type == OBJ_TAG) {
		o = parse_object(the_repository, &o->oid);
		if (o && o->type == OBJ_TAG && ((struct tag *)o)->tagged)
			o = ((struct tag *)o)->tagged;
		else
			o = NULL;
	}
	return o;
}