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
struct stat {int st_size; } ;
struct futx {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EFTYPE ; 
 int O_CLOEXEC ; 
 int O_CREAT ; 
 int O_EXLOCK ; 
 int O_RDWR ; 
 int /*<<< orphan*/  _close (int) ; 
 int _fstat (int,struct stat*) ; 
 int _open (char const*,int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 

__attribute__((used)) static FILE *
futx_open(const char *file)
{
	FILE *fp;
	struct stat sb;
	int fd;

	fd = _open(file, O_CREAT|O_RDWR|O_EXLOCK|O_CLOEXEC, 0644);
	if (fd < 0)
		return (NULL);

	/* Safety check: never use broken files. */
	if (_fstat(fd, &sb) != -1 && sb.st_size % sizeof(struct futx) != 0) {
		_close(fd);
		errno = EFTYPE;
		return (NULL);
	}

	fp = fdopen(fd, "r+");
	if (fp == NULL) {
		_close(fd);
		return (NULL);
	}
	return (fp);
}