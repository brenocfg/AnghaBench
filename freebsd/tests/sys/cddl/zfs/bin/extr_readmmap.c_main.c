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
 char* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  MS_SYNC ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 char* calloc (int,size_t) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* mmap (int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ msync (char*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ munmap (char*,size_t) ; 
 int open (char*,int,int) ; 
 int optind ; 
 int /*<<< orphan*/  perror (char*) ; 
 int pread (int,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,size_t,...) ; 
 size_t random () ; 
 int /*<<< orphan*/  remove (char*) ; 
 int /*<<< orphan*/  srandom (unsigned int) ; 
 int /*<<< orphan*/  stderr ; 
 unsigned int time (int /*<<< orphan*/ *) ; 
 int write (int,char*,size_t) ; 

int
main(int argc, char **argv)
{
	char *filename = "badfile";
	size_t size = 4395;
	size_t idx = 0;
	char *buf = NULL;
	char *map = NULL;
	int fd = -1, bytes, retval = 0;
	unsigned seed;

	if (argc < 2 || optind == argc) {
		(void) fprintf(stderr,
		    "usage: %s <file name>\n", argv[0]);
		exit(1);
	}

	if ((buf = calloc(1, size)) == NULL) {
		perror("calloc");
		exit(1);
	}

	filename = argv[optind];

	(void) remove(filename);

	fd = open(filename, O_RDWR|O_CREAT|O_TRUNC, 0666);
	if (fd == -1) {
		perror("open to create");
		retval = 1;
		goto end;
	}

	bytes = write(fd, buf, size);
	if (bytes != size) {
		(void) printf("short write: %d != %ud\n", bytes, size);
		retval = 1;
		goto end;
	}

	map = mmap(0, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (map == MAP_FAILED) {
		perror("mmap");
		retval = 1;
		goto end;
	}
	seed = time(NULL);
	srandom(seed);

	idx = random() % size;
	map[idx] = 1;

	if (msync(map, size, MS_SYNC) != 0) {
		perror("msync");
		retval = 1;
		goto end;
	}

	if (munmap(map, size) != 0) {
		perror("munmap");
		retval = 1;
		goto end;
	}

	bytes = pread(fd, buf, size, 0);
	if (bytes != size) {
		(void) printf("short read: %d != %ud\n", bytes, size);
		retval = 1;
		goto end;
	}

	if (buf[idx] != 1) {
		(void) printf(
		    "bad data from read!  got buf[%ud]=%d, expected 1\n",
		    idx, buf[idx]);
		retval = 1;
		goto end;
	}

	(void) printf("good data from read: buf[%ud]=1\n", idx);
end:
	if (fd != -1) {
		(void) close(fd);
	}
	if (buf != NULL) {
		free(buf);
	}

	return (retval);
}