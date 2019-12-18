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
struct remote {scalar_t__ origin; } ;
struct refspec_item {char* src; scalar_t__ matching; scalar_t__ pattern; } ;
struct refspec {int nr; struct refspec_item* items; } ;
struct ref {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 struct refspec REFSPEC_INIT_PUSH ; 
 scalar_t__ REMOTE_UNCONFIGURED ; 
 int /*<<< orphan*/  _ (char*) ; 
 int count_refspec_match (char*,struct ref*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct ref* get_local_heads () ; 
 struct remote* pushremote_get (char const*) ; 
 int /*<<< orphan*/  refspec_appendn (struct refspec*,char const**,int) ; 
 int /*<<< orphan*/  refspec_clear (struct refspec*) ; 
 char* resolve_refdup (char*,int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

__attribute__((used)) static int push_check(int argc, const char **argv, const char *prefix)
{
	struct remote *remote;
	const char *superproject_head;
	char *head;
	int detached_head = 0;
	struct object_id head_oid;

	if (argc < 3)
		die("submodule--helper push-check requires at least 2 arguments");

	/*
	 * superproject's resolved head ref.
	 * if HEAD then the superproject is in a detached head state, otherwise
	 * it will be the resolved head ref.
	 */
	superproject_head = argv[1];
	argv++;
	argc--;
	/* Get the submodule's head ref and determine if it is detached */
	head = resolve_refdup("HEAD", 0, &head_oid, NULL);
	if (!head)
		die(_("Failed to resolve HEAD as a valid ref."));
	if (!strcmp(head, "HEAD"))
		detached_head = 1;

	/*
	 * The remote must be configured.
	 * This is to avoid pushing to the exact same URL as the parent.
	 */
	remote = pushremote_get(argv[1]);
	if (!remote || remote->origin == REMOTE_UNCONFIGURED)
		die("remote '%s' not configured", argv[1]);

	/* Check the refspec */
	if (argc > 2) {
		int i;
		struct ref *local_refs = get_local_heads();
		struct refspec refspec = REFSPEC_INIT_PUSH;

		refspec_appendn(&refspec, argv + 2, argc - 2);

		for (i = 0; i < refspec.nr; i++) {
			const struct refspec_item *rs = &refspec.items[i];

			if (rs->pattern || rs->matching)
				continue;

			/* LHS must match a single ref */
			switch (count_refspec_match(rs->src, local_refs, NULL)) {
			case 1:
				break;
			case 0:
				/*
				 * If LHS matches 'HEAD' then we need to ensure
				 * that it matches the same named branch
				 * checked out in the superproject.
				 */
				if (!strcmp(rs->src, "HEAD")) {
					if (!detached_head &&
					    !strcmp(head, superproject_head))
						break;
					die("HEAD does not match the named branch in the superproject");
				}
				/* fallthrough */
			default:
				die("src refspec '%s' must name a ref",
				    rs->src);
			}
		}
		refspec_clear(&refspec);
	}
	free(head);

	return 0;
}