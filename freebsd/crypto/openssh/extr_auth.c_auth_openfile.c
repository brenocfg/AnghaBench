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
struct passwd {int /*<<< orphan*/  pw_name; } ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auth_debug_add (char*,char*,char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  debug (char*,char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  logit (char*,char*,...) ; 
 int open (char const*,int) ; 
 scalar_t__ safe_path_fd (int /*<<< orphan*/ ,char const*,struct passwd*,char*,int) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  unset_nonblock (int) ; 

__attribute__((used)) static FILE *
auth_openfile(const char *file, struct passwd *pw, int strict_modes,
    int log_missing, char *file_type)
{
	char line[1024];
	struct stat st;
	int fd;
	FILE *f;

	if ((fd = open(file, O_RDONLY|O_NONBLOCK)) == -1) {
		if (log_missing || errno != ENOENT)
			debug("Could not open %s '%s': %s", file_type, file,
			   strerror(errno));
		return NULL;
	}

	if (fstat(fd, &st) < 0) {
		close(fd);
		return NULL;
	}
	if (!S_ISREG(st.st_mode)) {
		logit("User %s %s %s is not a regular file",
		    pw->pw_name, file_type, file);
		close(fd);
		return NULL;
	}
	unset_nonblock(fd);
	if ((f = fdopen(fd, "r")) == NULL) {
		close(fd);
		return NULL;
	}
	if (strict_modes &&
	    safe_path_fd(fileno(f), file, pw, line, sizeof(line)) != 0) {
		fclose(f);
		logit("Authentication refused: %s", line);
		auth_debug_add("Ignored %s: %s", file_type, line);
		return NULL;
	}

	return f;
}