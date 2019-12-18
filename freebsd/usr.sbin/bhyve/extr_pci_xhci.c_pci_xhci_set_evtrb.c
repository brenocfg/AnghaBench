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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct xhci_trb {int qwTrb0; int /*<<< orphan*/  dwTrb3; int /*<<< orphan*/  dwTrb2; } ;

/* Variables and functions */
 int /*<<< orphan*/  XHCI_TRB_2_ERROR_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XHCI_TRB_3_TYPE_SET (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pci_xhci_set_evtrb(struct xhci_trb *evtrb, uint64_t port, uint32_t errcode,
    uint32_t evtype)
{
	evtrb->qwTrb0 = port << 24;
	evtrb->dwTrb2 = XHCI_TRB_2_ERROR_SET(errcode);
	evtrb->dwTrb3 = XHCI_TRB_3_TYPE_SET(evtype);
}