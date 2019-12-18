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
struct tag {TYPE_1__* tagged; } ;
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct object {scalar_t__ type; } ;
struct TYPE_2__ {struct object_id oid; } ;

/* Variables and functions */
 scalar_t__ OBJ_TAG ; 
 int /*<<< orphan*/  error (char*,int,char const*) ; 
 scalar_t__ is_promisor_object (struct object_id*) ; 
 struct object* parse_object (struct repository*,struct object_id*) ; 
 int strlen (char const*) ; 

struct object *deref_tag(struct repository *r, struct object *o, const char *warn, int warnlen)
{
	struct object_id *last_oid = NULL;
	while (o && o->type == OBJ_TAG)
		if (((struct tag *)o)->tagged) {
			last_oid = &((struct tag *)o)->tagged->oid;
			o = parse_object(r, last_oid);
		} else {
			last_oid = NULL;
			o = NULL;
		}
	if (!o && warn) {
		if (last_oid && is_promisor_object(last_oid))
			return NULL;
		if (!warnlen)
			warnlen = strlen(warn);
		error("missing object referenced by '%.*s'", warnlen, warn);
	}
	return o;
}