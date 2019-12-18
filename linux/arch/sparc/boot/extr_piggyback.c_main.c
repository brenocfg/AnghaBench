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
struct stat {unsigned int st_size; } ;
typedef  int off_t ;

/* Variables and functions */
 unsigned int AOUT_TEXT_OFFSET ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 unsigned int align (unsigned int) ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int get_hdrs_offset (int,char*) ; 
 int /*<<< orphan*/  get_start_end (char*,unsigned int*,unsigned int*) ; 
 int is64bit ; 
 scalar_t__ lseek (int,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  st4 (char*,unsigned int) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 
 unsigned int write (int,char*,unsigned int) ; 

int main(int argc,char **argv)
{
	static char aout_magic[] = { 0x01, 0x03, 0x01, 0x07 };
	char buffer[1024];
	unsigned int i, start, end;
	off_t offset;
	struct stat s;
	int image, tail;

	if (argc != 5)
		usage();
	if (strcmp(argv[1], "64") == 0)
		is64bit = 1;
	if (stat (argv[4], &s) < 0)
		die(argv[4]);

	if (!get_start_end(argv[3], &start, &end)) {
		fprintf(stderr, "Could not determine start and end from %s\n",
		        argv[3]);
		exit(1);
	}
	if ((image = open(argv[2], O_RDWR)) < 0)
		die(argv[2]);
	if (read(image, buffer, 512) != 512)
		die(argv[2]);
	if (memcmp(buffer, aout_magic, 4) != 0) {
		fprintf (stderr, "Not a.out. Don't blame me.\n");
		exit(1);
	}
	/*
	 * We need to fill in values for
	 * sparc_ramdisk_image + sparc_ramdisk_size
	 * To locate these symbols search for the "HdrS" text which appear
	 * in the image a little before the gokernel symbol.
	 * See definition of these in init_32.S
	 */

	offset = get_hdrs_offset(image, argv[2]);
	/* skip HdrS + LINUX_VERSION_CODE + HdrS version */
	offset += 10;

	if (lseek(image, offset, 0) < 0)
		die("lseek");

	/*
	 * root_flags = 0
	 * root_dev = 1 (RAMDISK_MAJOR)
	 * ram_flags = 0
	 * sparc_ramdisk_image = "PAGE aligned address after _end")
	 * sparc_ramdisk_size = size of image
	 */
	st4(buffer, 0);
	st4(buffer + 4, 0x01000000);
	st4(buffer + 8, align(end + 32));
	st4(buffer + 12, s.st_size);

	if (write(image, buffer + 2, 14) != 14)
		die(argv[2]);

	/* For sparc64 update a_text and clear a_data + a_bss */
	if (is64bit)
	{
		if (lseek(image, 4, 0) < 0)
			die("lseek");
		/* a_text */
		st4(buffer, align(end + 32 + 8191) - (start & ~0x3fffffUL) +
		            s.st_size);
		/* a_data */
		st4(buffer + 4, 0);
		/* a_bss */
		st4(buffer + 8, 0);
		if (write(image, buffer, 12) != 12)
			die(argv[2]);
	}

	/* seek page aligned boundary in the image file and add boot image */
	if (lseek(image, AOUT_TEXT_OFFSET - start + align(end + 32), 0) < 0)
		die("lseek");
	if ((tail = open(argv[4], O_RDONLY)) < 0)
		die(argv[4]);
	while ((i = read(tail, buffer, 1024)) > 0)
		if (write(image, buffer, i) != i)
			die(argv[2]);
	if (close(image) < 0)
		die("close");
	if (close(tail) < 0)
		die("close");
	return 0;
}