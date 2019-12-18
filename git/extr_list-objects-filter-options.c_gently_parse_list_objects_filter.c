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
struct list_objects_filter_options {scalar_t__ choice; int /*<<< orphan*/  sparse_oid_name; int /*<<< orphan*/  tree_exclude_depth; int /*<<< orphan*/  blob_limit_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 scalar_t__ LOFC_BLOB_LIMIT ; 
 scalar_t__ LOFC_BLOB_NONE ; 
 scalar_t__ LOFC_SPARSE_OID ; 
 scalar_t__ LOFC_TREE_DEPTH ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ git_parse_ulong (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct list_objects_filter_options*,int /*<<< orphan*/ ,int) ; 
 int parse_combine_filter (struct list_objects_filter_options*,char const*,struct strbuf*) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static int gently_parse_list_objects_filter(
	struct list_objects_filter_options *filter_options,
	const char *arg,
	struct strbuf *errbuf)
{
	const char *v0;

	if (!arg)
		return 0;

	if (filter_options->choice)
		BUG("filter_options already populated");

	if (!strcmp(arg, "blob:none")) {
		filter_options->choice = LOFC_BLOB_NONE;
		return 0;

	} else if (skip_prefix(arg, "blob:limit=", &v0)) {
		if (git_parse_ulong(v0, &filter_options->blob_limit_value)) {
			filter_options->choice = LOFC_BLOB_LIMIT;
			return 0;
		}

	} else if (skip_prefix(arg, "tree:", &v0)) {
		if (!git_parse_ulong(v0, &filter_options->tree_exclude_depth)) {
			strbuf_addstr(errbuf, _("expected 'tree:<depth>'"));
			return 1;
		}
		filter_options->choice = LOFC_TREE_DEPTH;
		return 0;

	} else if (skip_prefix(arg, "sparse:oid=", &v0)) {
		filter_options->sparse_oid_name = xstrdup(v0);
		filter_options->choice = LOFC_SPARSE_OID;
		return 0;

	} else if (skip_prefix(arg, "sparse:path=", &v0)) {
		if (errbuf) {
			strbuf_addstr(
				errbuf,
				_("sparse:path filters support has been dropped"));
		}
		return 1;

	} else if (skip_prefix(arg, "combine:", &v0)) {
		return parse_combine_filter(filter_options, v0, errbuf);

	}
	/*
	 * Please update _git_fetch() in git-completion.bash when you
	 * add new filters
	 */

	strbuf_addf(errbuf, _("invalid filter-spec '%s'"), arg);

	memset(filter_options, 0, sizeof(*filter_options));
	return 1;
}