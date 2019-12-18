#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ MGSLPC_INFO ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_resources (TYPE_1__*) ; 
 scalar_t__ rx_alloc_buffers (TYPE_1__*) ; 

__attribute__((used)) static int claim_resources(MGSLPC_INFO *info)
{
	if (rx_alloc_buffers(info) < 0) {
		printk("Can't allocate rx buffer %s\n", info->device_name);
		release_resources(info);
		return -ENODEV;
	}
	return 0;
}