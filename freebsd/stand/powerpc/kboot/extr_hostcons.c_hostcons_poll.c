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
struct host_timeval {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int host_select (int,long*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct host_timeval*) ; 

__attribute__((used)) static int
hostcons_poll()
{
	struct host_timeval tv = {0,0};
	long fds = 1 << 0;
	int ret;

	ret = host_select(32, &fds, NULL, NULL, &tv);
	return (ret > 0);
}