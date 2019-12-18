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
struct rmtcallfd_list {int fd; int /*<<< orphan*/ * xprt; struct rmtcallfd_list* next; } ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 struct rmtcallfd_list* rmthead ; 

__attribute__((used)) static SVCXPRT *
find_rmtcallxprt_by_fd(int fd)
{
	struct rmtcallfd_list *rmt;

	for (rmt = rmthead; rmt != NULL; rmt = rmt->next) {
		if (fd == rmt->fd) {
			return (rmt->xprt);
		}
	}
	return (NULL);
}