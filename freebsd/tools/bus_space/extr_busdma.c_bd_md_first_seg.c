#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct obj** seg; } ;
struct TYPE_4__ {TYPE_1__ md; } ;
struct obj {int oid; TYPE_2__ u; } ;

/* Variables and functions */
 int BUSDMA_MD_BUS ; 
 int BUSDMA_MD_PHYS ; 
 int BUSDMA_MD_VIRT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  OBJ_TYPE_MD ; 
 int /*<<< orphan*/  errno ; 
 struct obj* obj_lookup (int,int /*<<< orphan*/ ) ; 

int
bd_md_first_seg(int mdid, int space)
{
	struct obj *md, *seg;

	md = obj_lookup(mdid, OBJ_TYPE_MD);
	if (md == NULL)
		return (-1);

	if (space != BUSDMA_MD_BUS && space != BUSDMA_MD_PHYS &&
	    space != BUSDMA_MD_VIRT) {
		errno = EINVAL;
		return (-1);
	}
	seg = md->u.md.seg[space];
	if (seg == NULL) {
		errno = ENXIO;
		return (-1);
	}
	return (seg->oid);
}