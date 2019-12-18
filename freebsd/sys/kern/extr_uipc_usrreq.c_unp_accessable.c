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
struct unpcb {int unp_gcflag; } ;
struct filedescent {struct file* fde_file; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int UNPGC_DEAD ; 
 int UNPGC_REF ; 
 struct unpcb* fptounp (struct file*) ; 
 int /*<<< orphan*/  unp_marked ; 

__attribute__((used)) static void
unp_accessable(struct filedescent **fdep, int fdcount)
{
	struct unpcb *unp;
	struct file *fp;
	int i;

	for (i = 0; i < fdcount; i++) {
		fp = fdep[i]->fde_file;
		if ((unp = fptounp(fp)) == NULL)
			continue;
		if (unp->unp_gcflag & UNPGC_REF)
			continue;
		unp->unp_gcflag &= ~UNPGC_DEAD;
		unp->unp_gcflag |= UNPGC_REF;
		unp_marked++;
	}
}