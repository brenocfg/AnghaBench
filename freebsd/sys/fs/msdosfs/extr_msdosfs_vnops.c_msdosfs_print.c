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
struct vop_print_args {int /*<<< orphan*/  a_vp; } ;
struct denode {TYPE_1__* de_pmp; int /*<<< orphan*/  de_diroffset; int /*<<< orphan*/  de_dirclust; int /*<<< orphan*/  de_StartCluster; } ;
struct TYPE_2__ {int /*<<< orphan*/  pm_dev; } ;

/* Variables and functions */
 struct denode* VTODE (int /*<<< orphan*/ ) ; 
 char* devtoname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 

__attribute__((used)) static int
msdosfs_print(struct vop_print_args *ap)
{
	struct denode *dep = VTODE(ap->a_vp);

	printf("\tstartcluster %lu, dircluster %lu, diroffset %lu, ",
	       dep->de_StartCluster, dep->de_dirclust, dep->de_diroffset);
	printf("on dev %s\n", devtoname(dep->de_pmp->pm_dev));
	return (0);
}