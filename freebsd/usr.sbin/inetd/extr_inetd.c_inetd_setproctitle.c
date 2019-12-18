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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  pbuf ;

/* Variables and functions */
 int NI_MAXHOST ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 int /*<<< orphan*/  getnameinfo (struct sockaddr*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ getpeername (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  setproctitle (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,...) ; 

void
inetd_setproctitle(const char *a, int s)
{
	socklen_t size;
	struct sockaddr_storage ss;
	char buf[80], pbuf[NI_MAXHOST];

	size = sizeof(ss);
	if (getpeername(s, (struct sockaddr *)&ss, &size) == 0) {
		getnameinfo((struct sockaddr *)&ss, size, pbuf, sizeof(pbuf),
			    NULL, 0, NI_NUMERICHOST);
		(void) sprintf(buf, "%s [%s]", a, pbuf);
	} else
		(void) sprintf(buf, "%s", a);
	setproctitle("%s", buf);
}