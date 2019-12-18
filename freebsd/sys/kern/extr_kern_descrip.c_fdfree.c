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
struct filedescent {int /*<<< orphan*/  fde_seqc; int /*<<< orphan*/ * fde_file; } ;
struct filedesc {struct filedescent* fd_ofiles; } ;

/* Variables and functions */
 int /*<<< orphan*/  fdefree_last (struct filedescent*) ; 
 int /*<<< orphan*/  fdunused (struct filedesc*,int) ; 
 int /*<<< orphan*/  seqc_write_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seqc_write_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
fdfree(struct filedesc *fdp, int fd)
{
	struct filedescent *fde;

	fde = &fdp->fd_ofiles[fd];
#ifdef CAPABILITIES
	seqc_write_begin(&fde->fde_seqc);
#endif
	fde->fde_file = NULL;
#ifdef CAPABILITIES
	seqc_write_end(&fde->fde_seqc);
#endif
	fdefree_last(fde);
	fdunused(fdp, fd);
}