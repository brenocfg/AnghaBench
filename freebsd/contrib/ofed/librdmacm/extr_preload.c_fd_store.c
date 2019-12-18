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
struct fd_info {int fd; int type; int state; } ;
typedef  enum fd_type { ____Placeholder_fd_type } fd_type ;
typedef  enum fd_fork_state { ____Placeholder_fd_fork_state } fd_fork_state ;

/* Variables and functions */
 int /*<<< orphan*/  idm ; 
 struct fd_info* idm_at (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void fd_store(int index, int fd, enum fd_type type, enum fd_fork_state state)
{
	struct fd_info *fdi;

	fdi = idm_at(&idm, index);
	fdi->fd = fd;
	fdi->type = type;
	fdi->state = state;
}