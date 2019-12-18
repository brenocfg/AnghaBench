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
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_main_ref_store (int /*<<< orphan*/ ) ; 
 int refs_create_reflog (int /*<<< orphan*/ ,char const*,int,struct strbuf*) ; 
 int /*<<< orphan*/  the_repository ; 

int safe_create_reflog(const char *refname, int force_create,
		       struct strbuf *err)
{
	return refs_create_reflog(get_main_ref_store(the_repository), refname,
				  force_create, err);
}