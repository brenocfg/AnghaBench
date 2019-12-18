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
struct stat {int st_mode; } ;
struct iovec {int dummy; } ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  int /*<<< orphan*/  device ;

/* Variables and functions */
 int S_IWGRP ; 
 char* _PATH_DEV ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 char const* ttymsg (struct iovec*,int,char*,int) ; 

__attribute__((used)) static const char *
ttymsg_check(struct iovec *iov, int iovcnt, char *line, int tmout)
{
	static char device[1024];
	static char errbuf[1024];
	struct stat sb;

	(void) snprintf(device, sizeof(device), "%s%s", _PATH_DEV, line);

	if (stat(device, &sb) < 0) {
		(void) snprintf(errbuf, sizeof(errbuf),
		    "%s: %s", device, strerror(errno));
		return (errbuf);
	}
	if ((sb.st_mode & S_IWGRP) == 0)
		/* Messages disabled. */
		return (NULL);
	return ttymsg(iov, iovcnt, line, tmout);
}