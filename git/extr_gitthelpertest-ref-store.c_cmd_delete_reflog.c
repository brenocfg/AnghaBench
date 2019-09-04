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
struct ref_store {int dummy; } ;

/* Variables and functions */
 char* notnull (int /*<<< orphan*/ ,char*) ; 
 int refs_delete_reflog (struct ref_store*,char const*) ; 

__attribute__((used)) static int cmd_delete_reflog(struct ref_store *refs, const char **argv)
{
	const char *refname = notnull(*argv++, "refname");

	return refs_delete_reflog(refs, refname);
}