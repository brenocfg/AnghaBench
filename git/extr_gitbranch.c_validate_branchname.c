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
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int ref_exists (int /*<<< orphan*/ ) ; 
 scalar_t__ strbuf_check_branch_ref (struct strbuf*,char const*) ; 

int validate_branchname(const char *name, struct strbuf *ref)
{
	if (strbuf_check_branch_ref(ref, name))
		die(_("'%s' is not a valid branch name."), name);

	return ref_exists(ref->buf);
}