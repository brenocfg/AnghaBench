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

/* Variables and functions */
 int /*<<< orphan*/  DEVINFO_ROOT_DEVICE ; 
 int /*<<< orphan*/  all_flag ; 
 int /*<<< orphan*/  devinfo_foreach_device_child (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  devinfo_free () ; 
 int /*<<< orphan*/ * devinfo_handle_to_device (int /*<<< orphan*/ ) ; 
 scalar_t__ devinfo_init () ; 
 scalar_t__ dump_flag ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_nomatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_unmatched ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* linker_hints ; 
 int /*<<< orphan*/  longopts ; 
 int /*<<< orphan*/ * nomatch_str ; 
 void* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  read_linker_hints () ; 
 int /*<<< orphan*/ * root ; 
 int /*<<< orphan*/  search_hints (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unbound_flag ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  verbose_flag ; 

int
main(int argc, char **argv)
{
	int ch;

	while ((ch = getopt_long(argc, argv, "adh:p:uv",
		    longopts, NULL)) != -1) {
		switch (ch) {
		case 'a':
			all_flag++;
			break;
		case 'd':
			dump_flag++;
			break;
		case 'h':
			linker_hints = optarg;
			break;
		case 'p':
			nomatch_str = optarg;
			break;
		case 'u':
			unbound_flag++;
			break;
		case 'v':
			verbose_flag++;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (argc >= 1)
		usage();

	read_linker_hints();
	if (dump_flag) {
		search_hints(NULL, NULL, NULL);
		exit(0);
	}

	if (devinfo_init())
		err(1, "devinfo_init");
	if ((root = devinfo_handle_to_device(DEVINFO_ROOT_DEVICE)) == NULL)
		errx(1, "can't find root device");
	if (nomatch_str != NULL)
		find_nomatch(nomatch_str);
	else
		devinfo_foreach_device_child(root, find_unmatched, (void *)0);
	devinfo_free();
}