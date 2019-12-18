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
typedef  int /*<<< orphan*/  va_list ;
struct cdev {char* si_name; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ devfs_dev_exists (char*) ; 
 int /*<<< orphan*/  devmtx ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vsnrprintf (char*,int,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
prep_devname(struct cdev *dev, const char *fmt, va_list ap)
{
	int len;
	char *from, *q, *s, *to;

	mtx_assert(&devmtx, MA_OWNED);

	len = vsnrprintf(dev->si_name, sizeof(dev->si_name), 32, fmt, ap);
	if (len > sizeof(dev->si_name) - 1)
		return (ENAMETOOLONG);

	/* Strip leading slashes. */
	for (from = dev->si_name; *from == '/'; from++)
		;

	for (to = dev->si_name; *from != '\0'; from++, to++) {
		/*
		 * Spaces and double quotation marks cause
		 * problems for the devctl(4) protocol.
		 * Reject names containing those characters.
		 */
		if (isspace(*from) || *from == '"')
			return (EINVAL);
		/* Treat multiple sequential slashes as single. */
		while (from[0] == '/' && from[1] == '/')
			from++;
		/* Trailing slash is considered invalid. */
		if (from[0] == '/' && from[1] == '\0')
			return (EINVAL);
		*to = *from;
	}
	*to = '\0';

	if (dev->si_name[0] == '\0')
		return (EINVAL);

	/* Disallow "." and ".." components. */
	for (s = dev->si_name;;) {
		for (q = s; *q != '/' && *q != '\0'; q++)
			;
		if (q - s == 1 && s[0] == '.')
			return (EINVAL);
		if (q - s == 2 && s[0] == '.' && s[1] == '.')
			return (EINVAL);
		if (*q != '/')
			break;
		s = q + 1;
	}

	if (devfs_dev_exists(dev->si_name) != 0)
		return (EEXIST);

	return (0);
}