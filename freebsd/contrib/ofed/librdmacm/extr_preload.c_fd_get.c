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
struct fd_info {int fd; int type; } ;
typedef  enum fd_type { ____Placeholder_fd_type } fd_type ;

/* Variables and functions */
 int fd_normal ; 
 int /*<<< orphan*/  idm ; 
 struct fd_info* idm_lookup (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline enum fd_type fd_get(int index, int *fd)
{
	struct fd_info *fdi;

	fdi = idm_lookup(&idm, index);
	if (fdi) {
		*fd = fdi->fd;
		return fdi->type;

	} else {
		*fd = index;
		return fd_normal;
	}
}