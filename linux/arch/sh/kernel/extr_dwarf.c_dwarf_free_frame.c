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
struct dwarf_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwarf_frame_free_regs (struct dwarf_frame*) ; 
 int /*<<< orphan*/  dwarf_frame_pool ; 
 int /*<<< orphan*/  mempool_free (struct dwarf_frame*,int /*<<< orphan*/ ) ; 

void dwarf_free_frame(struct dwarf_frame *frame)
{
	dwarf_frame_free_regs(frame);
	mempool_free(frame, dwarf_frame_pool);
}