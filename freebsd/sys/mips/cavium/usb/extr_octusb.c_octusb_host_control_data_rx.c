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
struct octusb_td {scalar_t__ remainder; TYPE_1__* qh; int /*<<< orphan*/  offset; int /*<<< orphan*/  pc; scalar_t__ error_any; } ;
struct TYPE_2__ {scalar_t__ fixup_actlen; scalar_t__ fixup_off; scalar_t__ fixup_buf; } ;

/* Variables and functions */
 scalar_t__ octusb_host_alloc_endpoint (struct octusb_td*) ; 
 int /*<<< orphan*/  usbd_copy_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static uint8_t
octusb_host_control_data_rx(struct octusb_td *td)
{
	uint32_t rem;

	/* allocate endpoint and check pending */
	if (octusb_host_alloc_endpoint(td))
		return (1);		/* busy */

	/* check error */
	if (td->error_any)
		return (0);		/* done */

	/* copy data from buffer */
	rem = td->qh->fixup_actlen - td->qh->fixup_off;

	if (rem > td->remainder)
		rem = td->remainder;

	usbd_copy_in(td->pc, td->offset, td->qh->fixup_buf +
	    td->qh->fixup_off + 8, rem);

	td->offset += rem;
	td->remainder -= rem;
	td->qh->fixup_off += rem;

	return (0);			/* done */
}