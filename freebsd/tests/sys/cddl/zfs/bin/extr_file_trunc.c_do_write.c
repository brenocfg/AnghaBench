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
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ bsize ; 
 scalar_t__ calloc (int,scalar_t__) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fsize ; 
 scalar_t__ lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char*,char*,scalar_t__) ; 
 scalar_t__ offset ; 
 int /*<<< orphan*/  perror (char*) ; 
 int random () ; 
 scalar_t__ read (int,char*,scalar_t__) ; 
 scalar_t__ rflag ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ vflag ; 
 scalar_t__ write (int,char*,scalar_t__) ; 

__attribute__((used)) static void
do_write(int fd)
{
	off_t	roffset = 0;
	char 	*buf = NULL;
	char 	*rbuf = NULL;

	buf = (char *)calloc(1, bsize);
	rbuf = (char *)calloc(1, bsize);
	if (buf == NULL || rbuf == NULL) {
		perror("malloc");
		exit(4);
	}

	roffset = random() % fsize;
	if (lseek(fd, (offset + roffset), SEEK_SET) < 0) {
		perror("lseek");
		exit(5);
	}

	strcpy(buf, "ZFS Test Suite Truncation Test");
	if (write(fd, buf, bsize) < bsize) {
		perror("write");
		exit(6);
	}

	if (rflag) {
		if (lseek(fd, (offset + roffset), SEEK_SET) < 0) {
			perror("lseek");
			exit(7);
		}

		if (read(fd, rbuf, bsize) < bsize) {
			perror("read");
			exit(8);
		}

		if (memcmp(buf, rbuf, bsize) != 0) {
			perror("memcmp");
			exit(9);
		}
	}
	if (vflag) {
		(void) fprintf(stderr,
		    "Wrote to offset %ld\n", (offset + roffset));
		if (rflag) {
			(void) fprintf(stderr,
			    "Read back from offset %ld\n", (offset + roffset));
		}
	}

	(void) free(buf);
	(void) free(rbuf);
}