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

/* Variables and functions */
 int /*<<< orphan*/  get_main_ref_store (int /*<<< orphan*/ ) ; 
 int refs_copy_existing_ref (int /*<<< orphan*/ ,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  the_repository ; 

int copy_existing_ref(const char *oldref, const char *newref, const char *logmsg)
{
	return refs_copy_existing_ref(get_main_ref_store(the_repository), oldref, newref, logmsg);
}