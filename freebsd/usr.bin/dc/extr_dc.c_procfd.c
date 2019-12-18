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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EISDIR ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  eval () ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  reset_bmachine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  src ; 
 int /*<<< orphan*/  src_setstream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
procfd(int fd, char *fname) {
	struct stat st;
	FILE *file;

	file = fdopen(fd, "r");
	if (file == NULL)
		err(1, "cannot open file %s", fname);
	if (fstat(fileno(file), &st) == -1)
		err(1, "%s", fname);
	if (S_ISDIR(st.st_mode)) {
		errno = EISDIR;
		err(1, "%s", fname);
	}                
	src_setstream(&src, file);
	reset_bmachine(&src);
	eval();
	fclose(file);
}