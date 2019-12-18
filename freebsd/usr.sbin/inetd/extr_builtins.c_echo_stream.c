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
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inetd_setproctitle (int /*<<< orphan*/ ,int) ; 
 int read (int,char*,int) ; 
 scalar_t__ write (int,char*,int) ; 

__attribute__((used)) static void
echo_stream(int s, struct servtab *sep)
{
	char buffer[BUFSIZE];
	int i;

	inetd_setproctitle(sep->se_service, s);
	while ((i = read(s, buffer, sizeof(buffer))) > 0 &&
	    write(s, buffer, i) > 0)
		;
	exit(0);
}