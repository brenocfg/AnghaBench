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

/* Variables and functions */
 int /*<<< orphan*/  alarm_errno ; 
 int /*<<< orphan*/  alarm_id ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ksem_post (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
alarm_handler(int signo)
{

	if (ksem_post(alarm_id) < 0)
		alarm_errno = errno;
}