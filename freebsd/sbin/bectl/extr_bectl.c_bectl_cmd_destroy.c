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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int BE_DESTROY_AUTOORIGIN ; 
 int BE_DESTROY_FORCE ; 
 int BE_DESTROY_ORIGIN ; 
 int BE_MAXPATHLEN ; 
 int /*<<< orphan*/  be ; 
 int be_destroy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ be_get_dataset_props (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be_is_auto_snapshot_name (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ be_prop_list_alloc (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  be_prop_list_free (int /*<<< orphan*/ *) ; 
 scalar_t__ be_root_concat (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int usage (int) ; 

__attribute__((used)) static int
bectl_cmd_destroy(int argc, char *argv[])
{
	nvlist_t *props;
	char *origin, *target, targetds[BE_MAXPATHLEN];
	int err, flags, opt;

	flags = 0;
	while ((opt = getopt(argc, argv, "Fo")) != -1) {
		switch (opt) {
		case 'F':
			flags |= BE_DESTROY_FORCE;
			break;
		case 'o':
			flags |= BE_DESTROY_ORIGIN;
			break;
		default:
			fprintf(stderr, "bectl destroy: unknown option '-%c'\n",
			    optopt);
			return (usage(false));
		}
	}

	argc -= optind;
	argv += optind;

	if (argc != 1) {
		fprintf(stderr, "bectl destroy: wrong number of arguments\n");
		return (usage(false));
	}

	target = argv[0];

	/* We'll emit a notice if there's an origin to be cleaned up */
	if ((flags & BE_DESTROY_ORIGIN) == 0 && strchr(target, '@') == NULL) {
		flags |= BE_DESTROY_AUTOORIGIN;
		if (be_root_concat(be, target, targetds) != 0)
			goto destroy;
		if (be_prop_list_alloc(&props) != 0)
			goto destroy;
		if (be_get_dataset_props(be, targetds, props) != 0) {
			be_prop_list_free(props);
			goto destroy;
		}
		if (nvlist_lookup_string(props, "origin", &origin) == 0 &&
		    !be_is_auto_snapshot_name(be, origin))
			fprintf(stderr, "bectl destroy: leaving origin '%s' intact\n",
			    origin);
		be_prop_list_free(props);
	}

destroy:
	err = be_destroy(be, target, flags);

	return (err);
}