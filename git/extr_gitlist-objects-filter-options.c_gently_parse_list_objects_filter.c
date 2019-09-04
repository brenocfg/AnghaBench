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
struct object_id {int dummy; } ;
struct object_context {int dummy; } ;
struct list_objects_filter_options {void* sparse_path_value; scalar_t__ choice; int /*<<< orphan*/  sparse_oid_value; int /*<<< orphan*/  tree_exclude_depth; int /*<<< orphan*/  blob_limit_value; void* filter_spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_OID_BLOB ; 
 scalar_t__ LOFC_BLOB_LIMIT ; 
 scalar_t__ LOFC_BLOB_NONE ; 
 scalar_t__ LOFC_SPARSE_OID ; 
 scalar_t__ LOFC_SPARSE_PATH ; 
 scalar_t__ LOFC_TREE_DEPTH ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  get_oid_with_context (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,struct object_id*,struct object_context*) ; 
 scalar_t__ git_parse_ulong (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct list_objects_filter_options*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oiddup (struct object_id*) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int gently_parse_list_objects_filter(
	struct list_objects_filter_options *filter_options,
	const char *arg,
	struct strbuf *errbuf)
{
	const char *v0;

	if (filter_options->choice) {
		if (errbuf) {
			strbuf_addstr(
				errbuf,
				_("multiple filter-specs cannot be combined"));
		}
		return 1;
	}

	filter_options->filter_spec = strdup(arg);

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
			if (errbuf) {
				strbuf_addstr(
					errbuf,
					_("expected 'tree:<depth>'"));
			}
			return 1;
		}
		filter_options->choice = LOFC_TREE_DEPTH;
		return 0;

	} else if (skip_prefix(arg, "sparse:oid=", &v0)) {
		struct object_context oc;
		struct object_id sparse_oid;

		/*
		 * Try to parse <oid-expression> into an OID for the current
		 * command, but DO NOT complain if we don't have the blob or
		 * ref locally.
		 */
		if (!get_oid_with_context(the_repository, v0, GET_OID_BLOB,
					  &sparse_oid, &oc))
			filter_options->sparse_oid_value = oiddup(&sparse_oid);
		filter_options->choice = LOFC_SPARSE_OID;
		return 0;

	} else if (skip_prefix(arg, "sparse:path=", &v0)) {
		filter_options->choice = LOFC_SPARSE_PATH;
		filter_options->sparse_path_value = strdup(v0);
		return 0;
	}
	/*
	 * Please update _git_fetch() in git-completion.bash when you
	 * add new filters
	 */

	if (errbuf)
		strbuf_addf(errbuf, "invalid filter-spec '%s'", arg);

	memset(filter_options, 0, sizeof(*filter_options));
	return 1;
}