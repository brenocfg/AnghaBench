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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct rbd_device {int /*<<< orphan*/  object_map_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rbd_object_map_get (struct rbd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 rbd_object_map_get(struct rbd_device *rbd_dev, u64 objno)
{
	u8 state;

	spin_lock(&rbd_dev->object_map_lock);
	state = __rbd_object_map_get(rbd_dev, objno);
	spin_unlock(&rbd_dev->object_map_lock);
	return state;
}