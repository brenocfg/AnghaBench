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
struct TYPE_5__ {struct obj* next; int /*<<< orphan*/  size; scalar_t__ address; } ;
struct TYPE_4__ {struct obj** seg; } ;
struct TYPE_6__ {TYPE_2__ seg; TYPE_1__ md; } ;
struct obj {TYPE_3__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  munmap (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obj_free (struct obj*) ; 

__attribute__((used)) static int
bd_md_del_segs(struct obj *md, int type, int unmap)
{
	struct obj *seg, *seg0;

	for (seg = md->u.md.seg[type]; seg != NULL; seg = seg0) {
		if (unmap)
			munmap((void *)seg->u.seg.address, seg->u.seg.size);
		seg0 = seg->u.seg.next;
		obj_free(seg);
	}
	return (0);
}