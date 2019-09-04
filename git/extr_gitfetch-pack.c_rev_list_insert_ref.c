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
struct object_id {int dummy; } ;
struct object {scalar_t__ type; } ;
struct fetch_negotiator {int /*<<< orphan*/  (* add_tip ) (struct fetch_negotiator*,struct commit*) ;} ;
struct commit {int dummy; } ;

/* Variables and functions */
 scalar_t__ OBJ_COMMIT ; 
 struct object* deref_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_object (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  stub1 (struct fetch_negotiator*,struct commit*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int rev_list_insert_ref(struct fetch_negotiator *negotiator,
			       const char *refname,
			       const struct object_id *oid)
{
	struct object *o = deref_tag(the_repository,
				     parse_object(the_repository, oid),
				     refname, 0);

	if (o && o->type == OBJ_COMMIT)
		negotiator->add_tip(negotiator, (struct commit *)o);

	return 0;
}