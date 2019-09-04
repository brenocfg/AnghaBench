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
 int /*<<< orphan*/  each_ref ; 
 char* notnull (int /*<<< orphan*/ ,char*) ; 
 int refs_for_each_ref_in (struct ref_store*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmd_for_each_ref(struct ref_store *refs, const char **argv)
{
	const char *prefix = notnull(*argv++, "prefix");

	return refs_for_each_ref_in(refs, prefix, each_ref, NULL);
}