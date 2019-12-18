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
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_3__ {int /*<<< orphan*/  address; } ;
struct TYPE_4__ {TYPE_1__ seg; } ;
struct obj {TYPE_2__ u; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OBJ_TYPE_SEG ; 
 int errno ; 
 struct obj* obj_lookup (int,int /*<<< orphan*/ ) ; 

int
bd_seg_get_addr(int sid, u_long *addr_p)
{
	struct obj *seg;

	if (addr_p == NULL)
		return (EINVAL);

	seg = obj_lookup(sid, OBJ_TYPE_SEG);
	if (seg == NULL)
		return (errno);

	*addr_p = seg->u.seg.address;
	return (0);
}