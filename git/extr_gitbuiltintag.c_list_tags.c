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
struct ref_sorting {int dummy; } ;
struct ref_format {char* format; } ;
struct ref_filter {int lines; int with_commit_tag_algo; } ;
struct ref_array {int nr; int /*<<< orphan*/ * items; } ;
typedef  int /*<<< orphan*/  array ;

/* Variables and functions */
 int /*<<< orphan*/  FILTER_REFS_TAGS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_refs (struct ref_array*,struct ref_filter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memset (struct ref_array*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ref_array_clear (struct ref_array*) ; 
 int /*<<< orphan*/  ref_array_sort (struct ref_sorting*,struct ref_array*) ; 
 int /*<<< orphan*/  show_ref_array_item (int /*<<< orphan*/ ,struct ref_format*) ; 
 scalar_t__ verify_ref_format (struct ref_format*) ; 
 char* xstrfmt (char*,char*,int) ; 

__attribute__((used)) static int list_tags(struct ref_filter *filter, struct ref_sorting *sorting,
		     struct ref_format *format)
{
	struct ref_array array;
	char *to_free = NULL;
	int i;

	memset(&array, 0, sizeof(array));

	if (filter->lines == -1)
		filter->lines = 0;

	if (!format->format) {
		if (filter->lines) {
			to_free = xstrfmt("%s %%(contents:lines=%d)",
					  "%(align:15)%(refname:lstrip=2)%(end)",
					  filter->lines);
			format->format = to_free;
		} else
			format->format = "%(refname:lstrip=2)";
	}

	if (verify_ref_format(format))
		die(_("unable to parse format string"));
	filter->with_commit_tag_algo = 1;
	filter_refs(&array, filter, FILTER_REFS_TAGS);
	ref_array_sort(sorting, &array);

	for (i = 0; i < array.nr; i++)
		show_ref_array_item(array.items[i], format);
	ref_array_clear(&array);
	free(to_free);

	return 0;
}