#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ features; scalar_t__ size; } ;
struct rbd_device {TYPE_1__ mapping; } ;

/* Variables and functions */

__attribute__((used)) static void rbd_dev_mapping_clear(struct rbd_device *rbd_dev)
{
	rbd_dev->mapping.size = 0;
	rbd_dev->mapping.features = 0;
}