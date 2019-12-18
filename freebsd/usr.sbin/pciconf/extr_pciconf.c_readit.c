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
struct pcisel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  _PATH_DEVPCI ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 struct pcisel getsel (char const*) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  readone (int,struct pcisel*,long,int) ; 
 long strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
readit(const char *name, const char *reg, int width)
{
	long rstart;
	long rend;
	long r;
	char *end;
	int i;
	int fd;
	struct pcisel sel;

	fd = open(_PATH_DEVPCI, O_RDWR, 0);
	if (fd < 0)
		err(1, "%s", _PATH_DEVPCI);

	rend = rstart = strtol(reg, &end, 0);
	if (end && *end == ':') {
		end++;
		rend = strtol(end, (char **) 0, 0);
	}
	sel = getsel(name);
	for (i = 1, r = rstart; r <= rend; i++, r += width) {
		readone(fd, &sel, r, width);
		if (i && !(i % 8))
			putchar(' ');
		putchar(i % (16/width) ? ' ' : '\n');
	}
	if (i % (16/width) != 1)
		putchar('\n');
	close(fd);
}