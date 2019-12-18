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
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int EFBIG ; 
 scalar_t__ OFF_MAX ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SIGXFSZ ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sigset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigxfsz ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  usage (char*) ; 
 int write (int,char*,int) ; 

int
main(int argc, char **argv)
{
	int		fd = 0;
	off_t		offset = (OFF_MAX - 1);
	off_t		lseek_ret = 0;
	int		write_ret = 0;
	int		err = 0;
	char		mybuf[5];
	char		*testfile;

	if (argc != 2) {
		usage(argv[0]);
	}

	(void) sigset(SIGXFSZ, sigxfsz);

	testfile = strdup(argv[1]);

	fd = open(testfile, O_CREAT | O_RDWR);
	if (fd < 0) {
		perror("Failed to create testfile");
		err = errno;
		goto out;
	}

	lseek_ret = lseek(fd, offset, SEEK_SET);
	if (lseek_ret < 0) {
		perror("Failed to seek to end of testfile");
		err = errno;
		goto out;
	}

	write_ret = write(fd, mybuf, 1);
	if (write_ret < 0) {
		perror("Failed to write to end of file");
		err = errno;
		goto out;
	}

	offset = 0;
	lseek_ret = lseek(fd, offset, SEEK_CUR);
	if (lseek_ret < 0) {
		perror("Failed to seek to end of file");
		err = errno;
		goto out;
	}

	write_ret = write(fd, mybuf, 1);
	if (write_ret < 0) {
		if (errno == EFBIG) {
			(void) printf("write errno=EFBIG: success\n");
			err = 0;
		} else {
			perror("Did not receive EFBIG");
			err = errno;
		}
	} else {
		(void) printf("write completed successfully, test failed\n");
		err = 1;
	}

out:
	(void) unlink(testfile);
	free(testfile);
	return (err);
}