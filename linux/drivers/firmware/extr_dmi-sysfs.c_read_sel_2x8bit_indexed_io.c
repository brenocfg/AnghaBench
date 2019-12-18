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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  data_addr; scalar_t__ index_addr; } ;
struct dmi_system_event_log {TYPE_1__ io; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_port_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static u8 read_sel_2x8bit_indexed_io(const struct dmi_system_event_log *sel,
				     loff_t offset)
{
	u8 ret;

	mutex_lock(&io_port_lock);
	outb((u8)offset, sel->io.index_addr);
	outb((u8)(offset >> 8), sel->io.index_addr + 1);
	ret = inb(sel->io.data_addr);
	mutex_unlock(&io_port_lock);
	return ret;
}