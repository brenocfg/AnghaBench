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
typedef  scalar_t__ u16 ;
struct bcma_device {scalar_t__ io_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  writew (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void bcma_host_soc_write16(struct bcma_device *core, u16 offset,
				 u16 value)
{
	writew(value, core->io_addr + offset);
}