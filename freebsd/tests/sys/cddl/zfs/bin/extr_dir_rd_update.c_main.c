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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int O_RDONLY ; 
 int O_SYNC ; 
 int /*<<< orphan*/  close (int) ; 
 char* dirpath ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int fchown (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int mkdir (char*,int) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strlen (char*) ; 

int
main(int argc, char **argv)
{
	char *cp1 = "";
	int i = 0;
	int ret = 0;
	int testdd = 0;
	pid_t pid;
	static const int op_num = 5;

	if (argc == 1) {
		(void) printf("Usage: %s <mount point>\n", argv[0]);
		exit(-1);
	}
	for (i = 0; i < 256; i++) {
		dirpath[i] = 0;
	}

	cp1 = argv[1];
	(void) strcpy(&dirpath[0], (const char *)cp1);
	(void) strcat(&dirpath[strlen(dirpath)], "TMP_DIR");

	ret = mkdir(dirpath, 0777);
	if (ret != 0) {
		if (errno != EEXIST) {
			(void) printf(
			"%s: mkdir(<%s>, 0777) failed: errno (decimal)=%d\n",
				argv[0], dirpath, errno);
			exit(-1);
		}
	}
	testdd = open(dirpath, O_RDONLY|O_SYNC);
	if (testdd < 0) {
		(void) printf(
"%s: open(<%s>, O_RDONLY|O_SYNC) failed: errno (decimal)=%d\n",
			argv[0], dirpath, errno);
		exit(-1);
	} else {
		(void) close(testdd);
	}
	pid = fork();
	if (pid > 0) {
		int fd = open(dirpath, O_RDONLY|O_SYNC);
		char buf[16];
		int rdret;
		int j = 0;

		while (j < op_num) {
			(void) sleep(1);
			rdret = read(fd, buf, 16);
			if (rdret == -1) {
				(void) printf("readdir failed");
			}
			j++;
		}
	} else if (pid == 0) {
		int fd = open(dirpath, O_RDONLY);
		int chownret;
		int k = 0;

		while (k < op_num) {
			(void) sleep(1);
			chownret = fchown(fd, 0, 0);
			if (chownret == -1) {
				(void) printf("chown failed");
			}

			k++;
		}
	}

	return (0);
}