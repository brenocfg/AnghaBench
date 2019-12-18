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
struct TYPE_2__ {scalar_t__ cpu_notes_buf_size; scalar_t__ cpu_notes_buf_vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  fadump_free_buffer (scalar_t__,scalar_t__) ; 
 TYPE_1__ fw_dump ; 

void fadump_free_cpu_notes_buf(void)
{
	if (!fw_dump.cpu_notes_buf_vaddr)
		return;

	fadump_free_buffer(fw_dump.cpu_notes_buf_vaddr,
			   fw_dump.cpu_notes_buf_size);
	fw_dump.cpu_notes_buf_vaddr = 0;
	fw_dump.cpu_notes_buf_size = 0;
}