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
struct strbuf {int len; char* buf; } ;
struct list_objects_filter_options {int /*<<< orphan*/  choice; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOFC_COMBINE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  list_objects_filter_release (struct list_objects_filter_options*) ; 
 int /*<<< orphan*/  memset (struct list_objects_filter_options*,int /*<<< orphan*/ ,int) ; 
 int parse_combine_subfilter (struct list_objects_filter_options*,struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_list_free (struct strbuf**) ; 
 int /*<<< orphan*/  strbuf_remove (struct strbuf*,size_t,int) ; 
 struct strbuf** strbuf_split_str (char const*,char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_combine_filter(
	struct list_objects_filter_options *filter_options,
	const char *arg,
	struct strbuf *errbuf)
{
	struct strbuf **subspecs = strbuf_split_str(arg, '+', 0);
	size_t sub;
	int result = 0;

	if (!subspecs[0]) {
		strbuf_addstr(errbuf, _("expected something after combine:"));
		result = 1;
		goto cleanup;
	}

	for (sub = 0; subspecs[sub] && !result; sub++) {
		if (subspecs[sub + 1]) {
			/*
			 * This is not the last subspec. Remove trailing "+" so
			 * we can parse it.
			 */
			size_t last = subspecs[sub]->len - 1;
			assert(subspecs[sub]->buf[last] == '+');
			strbuf_remove(subspecs[sub], last, 1);
		}
		result = parse_combine_subfilter(
			filter_options, subspecs[sub], errbuf);
	}

	filter_options->choice = LOFC_COMBINE;

cleanup:
	strbuf_list_free(subspecs);
	if (result) {
		list_objects_filter_release(filter_options);
		memset(filter_options, 0, sizeof(*filter_options));
	}
	return result;
}