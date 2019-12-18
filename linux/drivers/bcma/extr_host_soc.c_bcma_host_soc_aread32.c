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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct bcma_device {scalar_t__ io_wrap; } ;

/* Variables and functions */
 scalar_t__ WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static u32 bcma_host_soc_aread32(struct bcma_device *core, u16 offset)
{
	if (WARN_ONCE(!core->io_wrap, "Accessed core has no wrapper/agent\n"))
		return ~0;
	return readl(core->io_wrap + offset);
}