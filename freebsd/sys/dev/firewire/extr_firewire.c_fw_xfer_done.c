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
struct fw_xfer {int /*<<< orphan*/  (* hand ) (struct fw_xfer*) ;int /*<<< orphan*/ * fc; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_tl_free (int /*<<< orphan*/ *,struct fw_xfer*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stub1 (struct fw_xfer*) ; 

void
fw_xfer_done(struct fw_xfer *xfer)
{
	if (xfer->hand == NULL) {
		printf("hand == NULL\n");
		return;
	}

	if (xfer->fc == NULL)
		panic("fw_xfer_done: why xfer->fc is NULL?");

	fw_tl_free(xfer->fc, xfer);
	xfer->hand(xfer);
}