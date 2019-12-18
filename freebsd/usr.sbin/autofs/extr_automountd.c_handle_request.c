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
struct node {int /*<<< orphan*/ * n_location; int /*<<< orphan*/  n_config_line; int /*<<< orphan*/  n_config_file; } ;
struct autofs_daemon_request {char* adr_from; char* adr_path; char* adr_prefix; char* adr_key; char* adr_options; int /*<<< orphan*/  adr_id; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int auto_pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * auto_popen (char*,char*,char*,char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 char* checked_strdup (char const*) ; 
 char* concat (char*,char,char*) ; 
 int /*<<< orphan*/  create_subtree (struct node*,int) ; 
 int /*<<< orphan*/  done (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  exit_callback ; 
 int /*<<< orphan*/  lineno ; 
 int /*<<< orphan*/  log_debugx (char*,...) ; 
 int /*<<< orphan*/  log_errx (int,char*,...) ; 
 int /*<<< orphan*/  node_expand_ampersand (struct node*,char*) ; 
 int node_expand_defined (struct node*) ; 
 int /*<<< orphan*/  node_expand_wildcard (struct node*,char*) ; 
 struct node* node_find (struct node*,char*) ; 
 int node_has_wildcards (struct node*) ; 
 struct node* node_new_map (struct node*,char*,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 struct node* node_new_root () ; 
 char* node_options (struct node*) ; 
 int /*<<< orphan*/  parse_map (struct node*,char const*,char*,int*) ; 
 char* pick_option (char*,char**) ; 
 int /*<<< orphan*/  quick_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_id ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static void
handle_request(const struct autofs_daemon_request *adr, char *cmdline_options,
    bool incomplete_hierarchy)
{
	const char *map;
	struct node *root, *parent, *node;
	FILE *f;
	char *key, *options, *fstype, *nobrowse, *retrycnt, *tmp;
	int error;
	bool wildcards;

	log_debugx("got request %d: from %s, path %s, prefix \"%s\", "
	    "key \"%s\", options \"%s\"", adr->adr_id, adr->adr_from,
	    adr->adr_path, adr->adr_prefix, adr->adr_key, adr->adr_options);

	/*
	 * Try to notify the kernel about any problems.
	 */
	request_id = adr->adr_id;
	atexit(exit_callback);

	if (strncmp(adr->adr_from, "map ", 4) != 0) {
		log_errx(1, "invalid mountfrom \"%s\"; failing request",
		    adr->adr_from);
	}

	map = adr->adr_from + 4; /* 4 for strlen("map "); */
	root = node_new_root();
	if (adr->adr_prefix[0] == '\0' || strcmp(adr->adr_prefix, "/") == 0) {
		/*
		 * Direct map.  autofs(4) doesn't have a way to determine
		 * correct map key, but since it's a direct map, we can just
		 * use adr_path instead.
		 */
		parent = root;
		key = checked_strdup(adr->adr_path);
	} else {
		/*
		 * Indirect map.
		 */
		parent = node_new_map(root, checked_strdup(adr->adr_prefix),
		    NULL,  checked_strdup(map),
		    checked_strdup("[kernel request]"), lineno);

		if (adr->adr_key[0] == '\0')
			key = NULL;
		else
			key = checked_strdup(adr->adr_key);
	}

	/*
	 * "Wildcards" here actually means "make autofs(4) request
	 * automountd(8) action if the node being looked up does not
	 * exist, even though the parent is marked as cached".  This
	 * needs to be done for maps with wildcard entries, but also
	 * for special and executable maps.
	 */
	parse_map(parent, map, key, &wildcards);
	if (!wildcards)
		wildcards = node_has_wildcards(parent);
	if (wildcards)
		log_debugx("map may contain wildcard entries");
	else
		log_debugx("map does not contain wildcard entries");

	if (key != NULL)
		node_expand_wildcard(root, key);

	node = node_find(root, adr->adr_path);
	if (node == NULL) {
		log_errx(1, "map %s does not contain key for \"%s\"; "
		    "failing mount", map, adr->adr_path);
	}

	options = node_options(node);

	/*
	 * Append options from auto_master.
	 */
	options = concat(options, ',', adr->adr_options);

	/*
	 * Prepend options passed via automountd(8) command line.
	 */
	options = concat(cmdline_options, ',', options);

	if (node->n_location == NULL) {
		log_debugx("found node defined at %s:%d; not a mountpoint",
		    node->n_config_file, node->n_config_line);

		nobrowse = pick_option("nobrowse", &options);
		if (nobrowse != NULL && key == NULL) {
			log_debugx("skipping map %s due to \"nobrowse\" "
			    "option; exiting", map);
			done(0, true);

			/*
			 * Exit without calling exit_callback().
			 */
			quick_exit(0);
		}

		/*
		 * Not a mountpoint; create directories in the autofs mount
		 * and complete the request.
		 */
		create_subtree(node, incomplete_hierarchy);

		if (incomplete_hierarchy && key != NULL) {
			/*
			 * We still need to create the single subdirectory
			 * user is trying to access.
			 */
			tmp = concat(adr->adr_path, '/', key);
			node = node_find(root, tmp);
			if (node != NULL)
				create_subtree(node, false);
		}

		log_debugx("nothing to mount; exiting");
		done(0, wildcards);

		/*
		 * Exit without calling exit_callback().
		 */
		quick_exit(0);
	}

	log_debugx("found node defined at %s:%d; it is a mountpoint",
	    node->n_config_file, node->n_config_line);

	if (key != NULL)
		node_expand_ampersand(node, key);
	error = node_expand_defined(node);
	if (error != 0) {
		log_errx(1, "variable expansion failed for %s; "
		    "failing mount", adr->adr_path);
	}

	/*
	 * Append "automounted".
	 */
	options = concat(options, ',', "automounted");

	/*
	 * Remove "nobrowse", mount(8) doesn't understand it.
	 */
	pick_option("nobrowse", &options);

	/*
	 * Figure out fstype.
	 */
	fstype = pick_option("fstype=", &options);
	if (fstype == NULL) {
		log_debugx("fstype not specified in options; "
		    "defaulting to \"nfs\"");
		fstype = checked_strdup("nfs");
	}

	if (strcmp(fstype, "nfs") == 0) {
		/*
		 * The mount_nfs(8) command defaults to retry undefinitely.
		 * We do not want that behaviour, because it leaves mount_nfs(8)
		 * instances and automountd(8) children hanging forever.
		 * Disable retries unless the option was passed explicitly.
		 */
		retrycnt = pick_option("retrycnt=", &options);
		if (retrycnt == NULL) {
			log_debugx("retrycnt not specified in options; "
			    "defaulting to 1");
			options = concat(options, ',', "retrycnt=1");
		} else {
			options = concat(options, ',',
			    concat("retrycnt", '=', retrycnt));
		}
	}

	f = auto_popen("mount", "-t", fstype, "-o", options,
	    node->n_location, adr->adr_path, NULL);
	assert(f != NULL);
	error = auto_pclose(f);
	if (error != 0)
		log_errx(1, "mount failed");

	log_debugx("mount done; exiting");
	done(0, wildcards);

	/*
	 * Exit without calling exit_callback().
	 */
	quick_exit(0);
}