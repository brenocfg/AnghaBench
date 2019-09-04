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
struct transport {struct string_list* server_options; } ;
struct string_list {scalar_t__ nr; } ;
struct remote {char** url; int /*<<< orphan*/  url_nr; } ;
struct ref_sorting {int dummy; } ;
struct ref_array_item {char* symref; char* refname; int /*<<< orphan*/  objectname; } ;
struct ref_array {int nr; struct ref_array_item** items; } ;
struct ref {int /*<<< orphan*/  symref; int /*<<< orphan*/  old_oid; int /*<<< orphan*/  name; struct ref* next; } ;
struct option {char* member_2; char const** member_3; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct argv_array {int dummy; } ;
typedef  int /*<<< orphan*/  ref_array ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  OPTION_STRING ; 
 struct option OPT_BIT (char,char*,unsigned int*,int /*<<< orphan*/ ,unsigned int) ; 
 struct option OPT_BOOL (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 
 struct option OPT_END () ; 
 struct option OPT_REF_SORT (struct ref_sorting**) ; 
 struct option OPT_SET_INT_F (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct option OPT_STRING (int /*<<< orphan*/ ,char*,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct option OPT_STRING_LIST (char,char*,struct string_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct option OPT__QUIET (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_OPT_HIDDEN ; 
 int /*<<< orphan*/  PARSE_OPT_NOCOMPLETE ; 
 int /*<<< orphan*/  PARSE_OPT_STOP_AT_NON_OPTION ; 
 unsigned int REF_HEADS ; 
 unsigned int REF_NORMAL ; 
 unsigned int REF_TAGS ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 int /*<<< orphan*/  TRANS_OPT_UPLOADPACK ; 
 int /*<<< orphan*/  UNLEAK (struct ref_sorting*) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char*) ; 
 int /*<<< orphan*/  check_ref_type (struct ref const*,unsigned int) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ls_remote_usage ; 
 int /*<<< orphan*/  memset (struct ref_array*,int /*<<< orphan*/ ,int) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  ref_array_clear (struct ref_array*) ; 
 struct ref_array_item* ref_array_push (struct ref_array*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ref_array_sort (struct ref_sorting*,struct ref_array*) ; 
 struct remote* remote_get (char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tail_match (char const**,int /*<<< orphan*/ ) ; 
 scalar_t__ transport_disconnect (struct transport*) ; 
 struct transport* transport_get (struct remote*,int /*<<< orphan*/ *) ; 
 struct ref* transport_get_remote_refs (struct transport*,struct argv_array*) ; 
 int /*<<< orphan*/  transport_set_option (struct transport*,int /*<<< orphan*/ ,char const*) ; 
 char** xcalloc (int,int) ; 
 char* xstrdup_or_null (int /*<<< orphan*/ ) ; 
 char* xstrfmt (char*,char const*) ; 

int cmd_ls_remote(int argc, const char **argv, const char *prefix)
{
	const char *dest = NULL;
	unsigned flags = 0;
	int get_url = 0;
	int quiet = 0;
	int status = 0;
	int show_symref_target = 0;
	const char *uploadpack = NULL;
	const char **pattern = NULL;
	struct argv_array ref_prefixes = ARGV_ARRAY_INIT;
	int i;
	struct string_list server_options = STRING_LIST_INIT_DUP;

	struct remote *remote;
	struct transport *transport;
	const struct ref *ref;
	struct ref_array ref_array;
	static struct ref_sorting *sorting = NULL, **sorting_tail = &sorting;

	struct option options[] = {
		OPT__QUIET(&quiet, N_("do not print remote URL")),
		OPT_STRING(0, "upload-pack", &uploadpack, N_("exec"),
			   N_("path of git-upload-pack on the remote host")),
		{ OPTION_STRING, 0, "exec", &uploadpack, N_("exec"),
			   N_("path of git-upload-pack on the remote host"),
			   PARSE_OPT_HIDDEN },
		OPT_BIT('t', "tags", &flags, N_("limit to tags"), REF_TAGS),
		OPT_BIT('h', "heads", &flags, N_("limit to heads"), REF_HEADS),
		OPT_BIT(0, "refs", &flags, N_("do not show peeled tags"), REF_NORMAL),
		OPT_BOOL(0, "get-url", &get_url,
			 N_("take url.<base>.insteadOf into account")),
		OPT_REF_SORT(sorting_tail),
		OPT_SET_INT_F(0, "exit-code", &status,
			      N_("exit with exit code 2 if no matching refs are found"),
			      2, PARSE_OPT_NOCOMPLETE),
		OPT_BOOL(0, "symref", &show_symref_target,
			 N_("show underlying ref in addition to the object pointed by it")),
		OPT_STRING_LIST('o', "server-option", &server_options, N_("server-specific"), N_("option to transmit")),
		OPT_END()
	};

	memset(&ref_array, 0, sizeof(ref_array));

	argc = parse_options(argc, argv, prefix, options, ls_remote_usage,
			     PARSE_OPT_STOP_AT_NON_OPTION);
	dest = argv[0];

	if (argc > 1) {
		int i;
		pattern = xcalloc(argc, sizeof(const char *));
		for (i = 1; i < argc; i++) {
			pattern[i - 1] = xstrfmt("*/%s", argv[i]);
		}
	}

	if (flags & REF_TAGS)
		argv_array_push(&ref_prefixes, "refs/tags/");
	if (flags & REF_HEADS)
		argv_array_push(&ref_prefixes, "refs/heads/");

	remote = remote_get(dest);
	if (!remote) {
		if (dest)
			die("bad repository '%s'", dest);
		die("No remote configured to list refs from.");
	}
	if (!remote->url_nr)
		die("remote %s has no configured URL", dest);

	if (get_url) {
		printf("%s\n", *remote->url);
		UNLEAK(sorting);
		return 0;
	}

	transport = transport_get(remote, NULL);
	if (uploadpack != NULL)
		transport_set_option(transport, TRANS_OPT_UPLOADPACK, uploadpack);
	if (server_options.nr)
		transport->server_options = &server_options;

	ref = transport_get_remote_refs(transport, &ref_prefixes);
	if (transport_disconnect(transport)) {
		UNLEAK(sorting);
		return 1;
	}

	if (!dest && !quiet)
		fprintf(stderr, "From %s\n", *remote->url);
	for ( ; ref; ref = ref->next) {
		struct ref_array_item *item;
		if (!check_ref_type(ref, flags))
			continue;
		if (!tail_match(pattern, ref->name))
			continue;
		item = ref_array_push(&ref_array, ref->name, &ref->old_oid);
		item->symref = xstrdup_or_null(ref->symref);
	}

	if (sorting)
		ref_array_sort(sorting, &ref_array);

	for (i = 0; i < ref_array.nr; i++) {
		const struct ref_array_item *ref = ref_array.items[i];
		if (show_symref_target && ref->symref)
			printf("ref: %s\t%s\n", ref->symref, ref->refname);
		printf("%s\t%s\n", oid_to_hex(&ref->objectname), ref->refname);
		status = 0; /* we found something */
	}

	UNLEAK(sorting);
	ref_array_clear(&ref_array);
	return status;
}