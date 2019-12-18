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
 int refs_peel_ref (int /*<<< orphan*/ ,char const*,struct object_id*) ; 
 int /*<<< orphan*/  the_repository ; 

int peel_ref(const char *refname, struct object_id *oid)
{
	return refs_peel_ref(get_main_ref_store(the_repository), refname, oid);
}