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
struct usb_xfer {int /*<<< orphan*/  max_frame_size; int /*<<< orphan*/  buf_fixup; scalar_t__ frbuffers; } ;
struct uhci_mem_layout {int /*<<< orphan*/  max_frame_size; scalar_t__ buf_offset; int /*<<< orphan*/  fix_pc; scalar_t__ buf_pc; } ;

/* Variables and functions */

__attribute__((used)) static void
uhci_mem_layout_init(struct uhci_mem_layout *ml, struct usb_xfer *xfer)
{
	ml->buf_pc = xfer->frbuffers + 0;
	ml->fix_pc = xfer->buf_fixup;

	ml->buf_offset = 0;

	ml->max_frame_size = xfer->max_frame_size;
}