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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct octusb_td {int error_any; scalar_t__ remainder; TYPE_1__* qh; int /*<<< orphan*/  offset; int /*<<< orphan*/  pc; } ;
struct TYPE_2__ {scalar_t__ fixup_len; scalar_t__ fixup_off; scalar_t__ fixup_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 scalar_t__ octusb_host_alloc_endpoint (struct octusb_td*) ; 
 int /*<<< orphan*/  usbd_copy_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static uint8_t
octusb_host_control_data_tx(struct octusb_td *td)
{
	uint32_t rem;

	/* allocate endpoint and check pending */
	if (octusb_host_alloc_endpoint(td))
		return (1);		/* busy */

	/* check error */
	if (td->error_any)
		return (0);		/* done */

	rem = td->qh->fixup_len - td->qh->fixup_off;

	if (td->remainder > rem) {
		td->error_any = 1;
		DPRINTFN(1, "Excess setup transmit data\n");
		return (0);		/* done */
	}
	usbd_copy_out(td->pc, td->offset, td->qh->fixup_buf +
	    td->qh->fixup_off + 8, td->remainder);

	td->offset += td->remainder;
	td->qh->fixup_off += td->remainder;
	td->remainder = 0;

	return (0);			/* done */
}