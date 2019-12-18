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
typedef  int /*<<< orphan*/  time_t ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct servtab {int dummy; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 scalar_t__ check_loop (struct sockaddr*,struct servtab*) ; 
 char* ctime (int /*<<< orphan*/ *) ; 
 scalar_t__ recvfrom (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  sendto (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
daytime_dg(int s, struct servtab *sep)
{
	char buffer[256];
	time_t now;
	struct sockaddr_storage ss;
	socklen_t size;

	now = time((time_t *) 0);

	size = sizeof(ss);
	if (recvfrom(s, buffer, sizeof(buffer), 0,
		     (struct sockaddr *)&ss, &size) < 0)
		return;

	if (check_loop((struct sockaddr *)&ss, sep))
		return;

	(void) sprintf(buffer, "%.24s\r\n", ctime(&now));
	(void) sendto(s, buffer, strlen(buffer), 0,
		      (struct sockaddr *)&ss, size);
}