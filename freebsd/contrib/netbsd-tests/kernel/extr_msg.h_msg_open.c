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
struct msg_fds {int /*<<< orphan*/ * pfd; int /*<<< orphan*/ * cfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int pipe (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
msg_open(struct msg_fds *fds)
{
	if (pipe(fds->pfd) == -1)
		return -1;
	if (pipe(fds->cfd) == -1) {
		close(fds->pfd[0]);
		close(fds->pfd[1]);
		return -1;
	}
	return 0;
}