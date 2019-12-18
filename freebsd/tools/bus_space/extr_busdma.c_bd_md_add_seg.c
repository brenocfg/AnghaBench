#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_long ;
struct TYPE_5__ {int* nsegs; struct obj** seg; } ;
struct TYPE_4__ {void* size; void* address; } ;
struct TYPE_6__ {TYPE_2__ md; TYPE_1__ seg; } ;
struct obj {int refcnt; TYPE_3__ u; struct obj* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_TYPE_SEG ; 
 int errno ; 
 struct obj* obj_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bd_md_add_seg(struct obj *md, int type, u_long addr, u_long size)
{
	struct obj *seg;

	seg = obj_alloc(OBJ_TYPE_SEG);
	if (seg == NULL)
		return (errno);
	seg->refcnt = 1;
	seg->parent = md;
	seg->u.seg.address = addr;
	seg->u.seg.size = size;

	md->u.md.seg[type] = seg;
	md->u.md.nsegs[type] = 1;
	return (0);
}