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
struct servtab {int dummy; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 scalar_t__ check_loop (struct sockaddr*,struct servtab*) ; 
 int recvfrom (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  sendto (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 

__attribute__((used)) static void
echo_dg(int s, struct servtab *sep)
{
	char buffer[65536]; /* Should be sizeof(max datagram). */
	int i;
	socklen_t size;
	struct sockaddr_storage ss;

	size = sizeof(ss);
	if ((i = recvfrom(s, buffer, sizeof(buffer), 0,
			  (struct sockaddr *)&ss, &size)) < 0)
		return;

	if (check_loop((struct sockaddr *)&ss, sep))
		return;

	(void) sendto(s, buffer, i, 0, (struct sockaddr *)&ss, size);
}