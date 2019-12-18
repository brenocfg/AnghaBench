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
 int MAXPATHLEN ; 
 size_t atoi (char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memset (char*,char,size_t) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  readlink (char*,char*,size_t) ; 
 int symlink (char*,char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

int
main(int argc, char *argv[])
{
#ifdef __FreeBSD__
	char b[512], *sl;
	size_t len = atoi(argv[1]);
	sl = malloc(len);
	memset(sl, 'a', len);
	sl[len - 1] = 0;
	unlink("symlink");
	if (symlink(sl, "symlink") == -1)
		err(1, "symlink()");
	(void)readlink("symlink", b, len);
	unlink("symlink");
#else
	char b[MAXPATHLEN];
	size_t len = atoi(argv[1]);
	(void)readlink("/", b, len);
#endif
	(void)printf("%s\n", b);
	return 0;
}