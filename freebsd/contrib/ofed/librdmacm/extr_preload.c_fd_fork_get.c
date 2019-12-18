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
struct fd_info {scalar_t__ state; int fd; int type; } ;
typedef  enum fd_type { ____Placeholder_fd_type } fd_type ;

/* Variables and functions */
 scalar_t__ fd_fork_active ; 
 scalar_t__ fd_fork_passive ; 
 int fd_normal ; 
 int /*<<< orphan*/  fork_active (int) ; 
 int /*<<< orphan*/  fork_passive (int) ; 
 int /*<<< orphan*/  idm ; 
 struct fd_info* idm_lookup (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline enum fd_type fd_fork_get(int index, int *fd)
{
	struct fd_info *fdi;

	fdi = idm_lookup(&idm, index);
	if (fdi) {
		if (fdi->state == fd_fork_passive)
			fork_passive(index);
		else if (fdi->state == fd_fork_active)
			fork_active(index);
		*fd = fdi->fd;
		return fdi->type;

	} else {
		*fd = index;
		return fd_normal;
	}
}