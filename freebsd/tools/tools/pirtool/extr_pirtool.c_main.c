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
typedef  int /*<<< orphan*/  pir_table_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PIR_BASE ; 
 int /*<<< orphan*/  PIR_SIZE ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  _PATH_DEVMEM ; 
 int /*<<< orphan*/  banner () ; 
 int /*<<< orphan*/  basename (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dump_pir_table (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_pir_table (void*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int getopt (int,char**,char*) ; 
 void* mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	int ch, r;
	int err = -1;
	int mem_fd = -1;
	pir_table_t *pir = NULL;
	void *map_addr = MAP_FAILED;
	char *real_pir;

	progname = basename(argv[0]);
	while ((ch = getopt(argc, argv, "h")) != -1)
		switch (ch) {
		case 'h':
		default:
			usage();
	}
	argc -= optind;
	argv += optind;

	if (argc > 0)
		usage();

	banner();
	/*
	 * Map the PIR region into our process' linear space.
	 */
	if ((mem_fd = open(_PATH_DEVMEM, O_RDONLY)) == -1) {
		perror("open");
		goto cleanup;
	}
	map_addr = mmap(NULL, PIR_SIZE, PROT_READ, MAP_SHARED, mem_fd,
	    PIR_BASE);
	if (map_addr == MAP_FAILED) {
		perror("mmap");
		goto cleanup;
	}
	/*
	 * Find and print the PIR table.
	 */
	if ((pir = find_pir_table(map_addr)) == NULL) {
		fprintf(stderr, "PIR table signature not found.\r\n");
	} else {
		dump_pir_table(pir, map_addr);
		err = 0;
	}

cleanup:
	if (map_addr != MAP_FAILED)
		munmap(map_addr, PIR_SIZE);
	if (mem_fd != -1)
		close(mem_fd);

	exit ((err == 0) ? EXIT_SUCCESS : EXIT_FAILURE);
}