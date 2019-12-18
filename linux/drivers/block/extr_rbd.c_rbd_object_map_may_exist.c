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
 scalar_t__ rbd_object_map_get (struct rbd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_object_map (struct rbd_device*) ; 

__attribute__((used)) static bool rbd_object_map_may_exist(struct rbd_device *rbd_dev, u64 objno)
{
	u8 state;

	/* fall back to default logic if object map is disabled or invalid */
	if (!use_object_map(rbd_dev))
		return true;

	state = rbd_object_map_get(rbd_dev, objno);
	return state != OBJECT_NONEXISTENT;
}