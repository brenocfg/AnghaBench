#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct unpcb {int /*<<< orphan*/  unp_ino; } ;
struct stat {int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_dev; int /*<<< orphan*/  st_blksize; } ;
struct TYPE_2__ {int /*<<< orphan*/  sb_hiwat; } ;
struct socket {TYPE_1__ so_snd; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NODEV ; 
 struct unpcb* sotounpcb (struct socket*) ; 

__attribute__((used)) static int
uipc_sense(struct socket *so, struct stat *sb)
{
	struct unpcb *unp;

	unp = sotounpcb(so);
	KASSERT(unp != NULL, ("uipc_sense: unp == NULL"));

	sb->st_blksize = so->so_snd.sb_hiwat;
	sb->st_dev = NODEV;
	sb->st_ino = unp->unp_ino;
	return (0);
}