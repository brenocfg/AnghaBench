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
typedef  scalar_t__ uint32_t ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct servtab {int dummy; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  result ;

/* Variables and functions */
 scalar_t__ check_loop (struct sockaddr*,struct servtab*) ; 
 scalar_t__ machtime () ; 
 scalar_t__ recvfrom (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  sendto (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 

__attribute__((used)) static void
machtime_dg(int s, struct servtab *sep)
{
	uint32_t result;
	struct sockaddr_storage ss;
	socklen_t size;

	size = sizeof(ss);
	if (recvfrom(s, (char *)&result, sizeof(result), 0,
		     (struct sockaddr *)&ss, &size) < 0)
		return;

	if (check_loop((struct sockaddr *)&ss, sep))
		return;

	result = machtime();
	(void) sendto(s, (char *) &result, sizeof(result), 0,
		      (struct sockaddr *)&ss, size);
}