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
typedef  enum action_on_err { ____Placeholder_action_on_err } action_on_err ;

/* Variables and functions */
 int /*<<< orphan*/  get_main_ref_store (int /*<<< orphan*/ ) ; 
 int refs_update_ref (int /*<<< orphan*/ ,char const*,char const*,struct object_id const*,struct object_id const*,unsigned int,int) ; 
 int /*<<< orphan*/  the_repository ; 

int update_ref(const char *msg, const char *refname,
	       const struct object_id *new_oid,
	       const struct object_id *old_oid,
	       unsigned int flags, enum action_on_err onerr)
{
	return refs_update_ref(get_main_ref_store(the_repository), msg, refname, new_oid,
			       old_oid, flags, onerr);
}