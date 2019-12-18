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
typedef  int u8 ;
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct rbd_device {scalar_t__ object_map_size; } ;

/* Variables and functions */
 int BITS_PER_OBJ ; 
 int OBJS_PER_BYTE ; 
 scalar_t__ div_u64_rem (scalar_t__,int,int*) ; 
 int /*<<< orphan*/  rbd_assert (int) ; 

__attribute__((used)) static void __rbd_object_map_index(struct rbd_device *rbd_dev, u64 objno,
				   u64 *index, u8 *shift)
{
	u32 off;

	rbd_assert(objno < rbd_dev->object_map_size);
	*index = div_u64_rem(objno, OBJS_PER_BYTE, &off);
	*shift = (OBJS_PER_BYTE - off - 1) * BITS_PER_OBJ;
}