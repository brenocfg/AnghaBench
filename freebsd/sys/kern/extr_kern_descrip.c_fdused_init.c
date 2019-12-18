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
struct filedesc {int /*<<< orphan*/ * fd_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  NDBIT (int) ; 
 size_t NDSLOT (int) ; 
 int /*<<< orphan*/  fdisused (struct filedesc*,int) ; 

__attribute__((used)) static void
fdused_init(struct filedesc *fdp, int fd)
{

	KASSERT(!fdisused(fdp, fd), ("fd=%d is already used", fd));

	fdp->fd_map[NDSLOT(fd)] |= NDBIT(fd);
}