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
struct nitrox_vfdev {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ __NDEV_READY ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool nitrox_vfdev_ready(struct nitrox_vfdev *vfdev)
{
	return atomic_read(&vfdev->state) == __NDEV_READY;
}