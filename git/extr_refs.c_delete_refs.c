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
struct string_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_main_ref_store (int /*<<< orphan*/ ) ; 
 int refs_delete_refs (int /*<<< orphan*/ ,char const*,struct string_list*,unsigned int) ; 
 int /*<<< orphan*/  the_repository ; 

int delete_refs(const char *msg, struct string_list *refnames,
		unsigned int flags)
{
	return refs_delete_refs(get_main_ref_store(the_repository), msg, refnames, flags);
}