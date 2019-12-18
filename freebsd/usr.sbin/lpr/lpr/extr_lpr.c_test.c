#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct exec {int dummy; } ;
typedef  int /*<<< orphan*/  execb ;
struct TYPE_3__ {int st_mode; scalar_t__ st_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_BADMAG (struct exec) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int S_IFDIR ; 
 int S_IFMT ; 
 scalar_t__ access (char const*,int) ; 
 int checkwriteperm (char const*,char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* progname ; 
 int read (int,struct exec*,int) ; 
 scalar_t__ rflag ; 
 scalar_t__ stat (char const*,TYPE_1__*) ; 
 TYPE_1__ statb ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static int
test(const char *file)
{
	struct exec execb;
	size_t dlen;
	int fd;
	char *cp, *dirpath;

	if (access(file, 4) < 0) {
		printf("%s: cannot access %s\n", progname, file);
		return(-1);
	}
	if (stat(file, &statb) < 0) {
		printf("%s: cannot stat %s\n", progname, file);
		return(-1);
	}
	if ((statb.st_mode & S_IFMT) == S_IFDIR) {
		printf("%s: %s is a directory\n", progname, file);
		return(-1);
	}
	if (statb.st_size == 0) {
		printf("%s: %s is an empty file\n", progname, file);
		return(-1);
 	}
	if ((fd = open(file, O_RDONLY)) < 0) {
		printf("%s: cannot open %s\n", progname, file);
		return(-1);
	}
	/*
	 * XXX Shall we add a similar test for ELF?
	 */
	if (read(fd, &execb, sizeof(execb)) == sizeof(execb) &&
	    !N_BADMAG(execb)) {
		printf("%s: %s is an executable program", progname, file);
		goto error1;
	}
	(void) close(fd);
	if (rflag) {
		/*
		 * aside: note that 'cp' is technically a 'const char *'
		 * (because it points into 'file'), even though strrchr
		 * returns a value of type 'char *'.
		 */
		if ((cp = strrchr(file, '/')) == NULL) {
			if (checkwriteperm(file,".") == 0)
				return(1);
		} else {
			if (cp == file) {
				fd = checkwriteperm(file,"/");
			} else {
				/* strlcpy will change the '/' to '\0' */
				dlen = cp - file + 1;
				dirpath = malloc(dlen);
				strlcpy(dirpath, file, dlen);
				fd = checkwriteperm(file, dirpath);
				free(dirpath);
			}
			if (fd == 0)
				return(1);
		}
		printf("%s: %s: is not removable by you\n", progname, file);
	}
	return(0);

error1:
	printf(" and is unprintable\n");
	(void) close(fd);
	return(-1);
}