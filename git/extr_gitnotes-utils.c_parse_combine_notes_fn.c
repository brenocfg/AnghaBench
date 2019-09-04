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
typedef  int /*<<< orphan*/ * combine_notes_fn ;

/* Variables and functions */
 int /*<<< orphan*/ * combine_notes_cat_sort_uniq ; 
 int /*<<< orphan*/ * combine_notes_concatenate ; 
 int /*<<< orphan*/ * combine_notes_ignore ; 
 int /*<<< orphan*/ * combine_notes_overwrite ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

__attribute__((used)) static combine_notes_fn parse_combine_notes_fn(const char *v)
{
	if (!strcasecmp(v, "overwrite"))
		return combine_notes_overwrite;
	else if (!strcasecmp(v, "ignore"))
		return combine_notes_ignore;
	else if (!strcasecmp(v, "concatenate"))
		return combine_notes_concatenate;
	else if (!strcasecmp(v, "cat_sort_uniq"))
		return combine_notes_cat_sort_uniq;
	else
		return NULL;
}