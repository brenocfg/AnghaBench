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
struct node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_MASTER_PATH ; 
 char* concat (char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  defined_init () ; 
 int /*<<< orphan*/  defined_parse_and_add (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_caches () ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  log_init (int) ; 
 int /*<<< orphan*/  mount_unmount (struct node*) ; 
 int /*<<< orphan*/  node_expand_ampersand (struct node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_expand_defined (struct node*) ; 
 int /*<<< orphan*/  node_expand_indirect_maps (struct node*) ; 
 struct node* node_new_root () ; 
 int /*<<< orphan*/  node_print (struct node*,char*) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  parse_master (struct node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmount_automounted (int) ; 
 int /*<<< orphan*/  usage_automount () ; 

int
main_automount(int argc, char **argv)
{
	struct node *root;
	int ch, debug = 0, show_maps = 0;
	char *options = NULL;
	bool do_unmount = false, force_unmount = false, flush = false;

	/*
	 * Note that in automount(8), the only purpose of variable
	 * handling is to aid in debugging maps (automount -L).
	 */
	defined_init();

	while ((ch = getopt(argc, argv, "D:Lfco:uv")) != -1) {
		switch (ch) {
		case 'D':
			defined_parse_and_add(optarg);
			break;
		case 'L':
			show_maps++;
			break;
		case 'c':
			flush = true;
			break;
		case 'f':
			force_unmount = true;
			break;
		case 'o':
			options = concat(options, ',', optarg);
			break;
		case 'u':
			do_unmount = true;
			break;
		case 'v':
			debug++;
			break;
		case '?':
		default:
			usage_automount();
		}
	}
	argc -= optind;
	if (argc != 0)
		usage_automount();

	if (force_unmount && !do_unmount)
		usage_automount();

	log_init(debug);

	if (flush) {
		flush_caches();
		return (0);
	}

	if (do_unmount) {
		unmount_automounted(force_unmount);
		return (0);
	}

	root = node_new_root();
	parse_master(root, AUTO_MASTER_PATH);

	if (show_maps) {
		if (show_maps > 1) {
			node_expand_indirect_maps(root);
			node_expand_ampersand(root, NULL);
		}
		node_expand_defined(root);
		node_print(root, options);
		return (0);
	}

	mount_unmount(root);

	return (0);
}