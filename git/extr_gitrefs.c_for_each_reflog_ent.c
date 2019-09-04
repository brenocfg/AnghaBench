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
typedef  int /*<<< orphan*/  each_reflog_ent_fn ;

/* Variables and functions */
 int /*<<< orphan*/  get_main_ref_store (int /*<<< orphan*/ ) ; 
 int refs_for_each_reflog_ent (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  the_repository ; 

int for_each_reflog_ent(const char *refname, each_reflog_ent_fn fn,
			void *cb_data)
{
	return refs_for_each_reflog_ent(get_main_ref_store(the_repository), refname,
					fn, cb_data);
}