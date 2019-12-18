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
struct file_mapping {int dummy; } ;
struct file_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFNT_MAP_BOLD ; 
 int /*<<< orphan*/  VFNT_MAP_BOLD_RH ; 
 int /*<<< orphan*/  VFNT_MAP_NORMAL ; 
 int /*<<< orphan*/  assert (int) ; 
 void* atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dedup_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_mappings (int) ; 
 int getopt (int,char**,char*) ; 
 void* height ; 
 int /*<<< orphan*/  number_glyphs () ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 scalar_t__ parse_file (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_font_info () ; 
 int /*<<< orphan*/  set_height (void*) ; 
 int /*<<< orphan*/  set_width (void*) ; 
 int /*<<< orphan*/  usage () ; 
 void* width ; 
 scalar_t__ write_fnt (char*) ; 

int
main(int argc, char *argv[])
{
	int ch, verbose = 0;

	assert(sizeof(struct file_header) == 32);
	assert(sizeof(struct file_mapping) == 8);

	while ((ch = getopt(argc, argv, "h:vw:")) != -1) {
		switch (ch) {
		case 'h':
			height = atoi(optarg);
			break;
		case 'v':
			verbose = 1;
			break;
		case 'w':
			width = atoi(optarg);
			break;
		case '?':
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (argc < 2 || argc > 3)
		usage();

	set_width(width);
	set_height(height);

	if (parse_file(argv[0], VFNT_MAP_NORMAL) != 0)
		return (1);
	argc--;
	argv++;
	if (argc == 2) {
		if (parse_file(argv[0], VFNT_MAP_BOLD) != 0)
			return (1);
		argc--;
		argv++;
	}
	number_glyphs();
	dedup_mapping(VFNT_MAP_BOLD);
	dedup_mapping(VFNT_MAP_BOLD_RH);
	fold_mappings(0);
	fold_mappings(1);
	fold_mappings(2);
	fold_mappings(3);
	if (write_fnt(argv[0]) != 0)
		return (1);

	if (verbose)
		print_font_info();

	return (0);
}