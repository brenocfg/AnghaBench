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
struct TYPE_3__ {struct obj* next; } ;
struct TYPE_4__ {TYPE_1__ seg; } ;
struct obj {int oid; TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  OBJ_TYPE_SEG ; 
 int /*<<< orphan*/  errno ; 
 struct obj* obj_lookup (int,int /*<<< orphan*/ ) ; 

int
bd_md_next_seg(int mdid, int sid)
{
	struct obj *seg;

	seg = obj_lookup(sid, OBJ_TYPE_SEG);
	if (seg == NULL)
		return (-1);

	seg = seg->u.seg.next;
	if (seg == NULL) {
		errno = ENXIO;
		return (-1);
	}
	return (seg->oid);
}