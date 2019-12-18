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

/* Variables and functions */
 int /*<<< orphan*/  get_main_ref_store (int /*<<< orphan*/ ) ; 
 int refs_delete_ref (int /*<<< orphan*/ ,char const*,char const*,struct object_id const*,unsigned int) ; 
 int /*<<< orphan*/  the_repository ; 

int delete_ref(const char *msg, const char *refname,
	       const struct object_id *old_oid, unsigned int flags)
{
	return refs_delete_ref(get_main_ref_store(the_repository), msg, refname,
			       old_oid, flags);
}