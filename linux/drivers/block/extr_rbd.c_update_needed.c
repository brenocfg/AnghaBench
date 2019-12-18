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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct rbd_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ OBJECT_NONEXISTENT ; 
 scalar_t__ OBJECT_PENDING ; 
 scalar_t__ rbd_object_map_get (struct rbd_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool update_needed(struct rbd_device *rbd_dev, u64 objno, u8 new_state)
{
	u8 state = rbd_object_map_get(rbd_dev, objno);

	if (state == new_state ||
	    (new_state == OBJECT_PENDING && state == OBJECT_NONEXISTENT) ||
	    (new_state == OBJECT_NONEXISTENT && state != OBJECT_PENDING))
		return false;

	return true;
}