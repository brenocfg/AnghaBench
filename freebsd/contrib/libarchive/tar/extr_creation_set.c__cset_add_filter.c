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
struct filter_set {int program; char* filter_name; } ;
struct creation_set {int filter_count; struct filter_set* filters; } ;

/* Variables and functions */
 int /*<<< orphan*/  lafe_errc (int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ realloc (struct filter_set*,int) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static void
_cset_add_filter(struct creation_set *cset, int program, const char *filter)
{
	struct filter_set *new_ptr;
	char *new_filter;

	new_ptr = (struct filter_set *)realloc(cset->filters,
	    sizeof(*cset->filters) * (cset->filter_count + 1));
	if (new_ptr == NULL)
		lafe_errc(1, 0, "No memory");
	new_filter = strdup(filter);
	if (new_filter == NULL)
		lafe_errc(1, 0, "No memory");
	cset->filters = new_ptr;
	cset->filters[cset->filter_count].program = program;
	cset->filters[cset->filter_count].filter_name = new_filter;
	cset->filter_count++;
}