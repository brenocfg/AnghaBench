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
struct list_objects_filter_options {int sub_nr; struct list_objects_filter_options* sub; int /*<<< orphan*/  sub_alloc; int /*<<< orphan*/  filter_spec; int /*<<< orphan*/  choice; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW_BY (struct list_objects_filter_options*,int,int,int /*<<< orphan*/ ) ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_spec_append_urlencode (struct list_objects_filter_options*,char const*) ; 
 int gently_parse_list_objects_filter (struct list_objects_filter_options*,char const*,struct strbuf*) ; 
 int /*<<< orphan*/  string_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transform_to_combine_type (struct list_objects_filter_options*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

void parse_list_objects_filter(
	struct list_objects_filter_options *filter_options,
	const char *arg)
{
	struct strbuf errbuf = STRBUF_INIT;
	int parse_error;

	if (!filter_options->choice) {
		string_list_append(&filter_options->filter_spec, xstrdup(arg));

		parse_error = gently_parse_list_objects_filter(
			filter_options, arg, &errbuf);
	} else {
		/*
		 * Make filter_options an LOFC_COMBINE spec so we can trivially
		 * add subspecs to it.
		 */
		transform_to_combine_type(filter_options);

		string_list_append(&filter_options->filter_spec, xstrdup("+"));
		filter_spec_append_urlencode(filter_options, arg);
		ALLOC_GROW_BY(filter_options->sub, filter_options->sub_nr, 1,
			      filter_options->sub_alloc);

		parse_error = gently_parse_list_objects_filter(
			&filter_options->sub[filter_options->sub_nr - 1], arg,
			&errbuf);
	}
	if (parse_error)
		die("%s", errbuf.buf);
}