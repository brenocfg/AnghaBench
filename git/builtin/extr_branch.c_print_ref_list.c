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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct ref_sorting {int dummy; } ;
struct ref_format {char* format; int /*<<< orphan*/  use_color; } ;
struct ref_filter {int kind; scalar_t__ verbose; } ;
struct ref_array {int nr; int /*<<< orphan*/ * items; } ;
typedef  int /*<<< orphan*/  array ;

/* Variables and functions */
 int FILTER_REFS_INCLUDE_BROKEN ; 
 int FILTER_REFS_REMOTES ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  branch_use_color ; 
 char* build_format (struct ref_filter*,int,char const*) ; 
 int calc_maxwidth (struct ref_array*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  colopts ; 
 scalar_t__ column_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  filter_refs (struct ref_array*,struct ref_filter*,int) ; 
 scalar_t__ format_ref_array_item (int /*<<< orphan*/ ,struct ref_format*,struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ref_array*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  output ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  ref_array_clear (struct ref_array*) ; 
 int /*<<< orphan*/  ref_array_sort (struct ref_sorting*,struct ref_array*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  string_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ verify_ref_format (struct ref_format*) ; 

__attribute__((used)) static void print_ref_list(struct ref_filter *filter, struct ref_sorting *sorting, struct ref_format *format)
{
	int i;
	struct ref_array array;
	int maxwidth = 0;
	const char *remote_prefix = "";
	char *to_free = NULL;

	/*
	 * If we are listing more than just remote branches,
	 * then remote branches will have a "remotes/" prefix.
	 * We need to account for this in the width.
	 */
	if (filter->kind != FILTER_REFS_REMOTES)
		remote_prefix = "remotes/";

	memset(&array, 0, sizeof(array));

	filter_refs(&array, filter, filter->kind | FILTER_REFS_INCLUDE_BROKEN);

	if (filter->verbose)
		maxwidth = calc_maxwidth(&array, strlen(remote_prefix));

	if (!format->format)
		format->format = to_free = build_format(filter, maxwidth, remote_prefix);
	format->use_color = branch_use_color;

	if (verify_ref_format(format))
		die(_("unable to parse format string"));

	ref_array_sort(sorting, &array);

	for (i = 0; i < array.nr; i++) {
		struct strbuf out = STRBUF_INIT;
		struct strbuf err = STRBUF_INIT;
		if (format_ref_array_item(array.items[i], format, &out, &err))
			die("%s", err.buf);
		if (column_active(colopts)) {
			assert(!filter->verbose && "--column and --verbose are incompatible");
			 /* format to a string_list to let print_columns() do its job */
			string_list_append(&output, out.buf);
		} else {
			fwrite(out.buf, 1, out.len, stdout);
			putchar('\n');
		}
		strbuf_release(&err);
		strbuf_release(&out);
	}

	ref_array_clear(&array);
	free(to_free);
}