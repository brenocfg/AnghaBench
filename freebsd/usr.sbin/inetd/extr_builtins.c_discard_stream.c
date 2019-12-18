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
struct servtab {int /*<<< orphan*/  se_service; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int BUFSIZE ; 
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inetd_setproctitle (int /*<<< orphan*/ ,int) ; 
 int read (int,char*,int) ; 

__attribute__((used)) static void
discard_stream(int s, struct servtab *sep)
{
	int ret;
	char buffer[BUFSIZE];

	inetd_setproctitle(sep->se_service, s);
	while (1) {
		while ((ret = read(s, buffer, sizeof(buffer))) > 0)
			;
		if (ret == 0 || errno != EINTR)
			break;
	}
	exit(0);
}