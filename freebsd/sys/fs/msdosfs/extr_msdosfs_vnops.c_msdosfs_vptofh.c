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
struct vop_vptofh_args {scalar_t__ a_fhp; int /*<<< orphan*/  a_vp; } ;
struct denode {int /*<<< orphan*/  de_diroffset; int /*<<< orphan*/  de_dirclust; } ;
struct defid {int defid_len; int /*<<< orphan*/  defid_dirofs; int /*<<< orphan*/  defid_dirclust; } ;

/* Variables and functions */
 struct denode* VTODE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
msdosfs_vptofh(struct vop_vptofh_args *ap)
{
	struct denode *dep;
	struct defid *defhp;

	dep = VTODE(ap->a_vp);
	defhp = (struct defid *)ap->a_fhp;
	defhp->defid_len = sizeof(struct defid);
	defhp->defid_dirclust = dep->de_dirclust;
	defhp->defid_dirofs = dep->de_diroffset;
	/* defhp->defid_gen = dep->de_gen; */
	return (0);
}