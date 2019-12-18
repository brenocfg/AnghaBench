#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct ioat_softc {int /*<<< orphan*/  dmaengine; int /*<<< orphan*/  head; } ;
struct TYPE_6__ {int null; } ;
struct TYPE_5__ {int completion_update; int /*<<< orphan*/  op; } ;
struct TYPE_7__ {TYPE_2__ control; TYPE_1__ control_generic; scalar_t__ control_raw; } ;
struct ioat_dma_hw_descriptor {int size; TYPE_3__ u; scalar_t__ dest_addr; scalar_t__ src_addr; } ;
struct bus_dmadesc {int /*<<< orphan*/ * callback_arg; int /*<<< orphan*/ * callback_fn; } ;
struct ioat_descriptor {struct bus_dmadesc bus_dmadesc; } ;
struct TYPE_8__ {struct ioat_dma_hw_descriptor dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  IOAT_CHANERR_OFFSET ; 
 int /*<<< orphan*/  IOAT_CHANERR_STR ; 
 int /*<<< orphan*/  IOAT_OP_COPY ; 
 int /*<<< orphan*/  ioat_acquire (int /*<<< orphan*/ *) ; 
 scalar_t__ ioat_get_chansts (struct ioat_softc*) ; 
 TYPE_4__* ioat_get_descriptor (struct ioat_softc*,int /*<<< orphan*/ ) ; 
 struct ioat_descriptor* ioat_get_ring_entry (struct ioat_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioat_log_message (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ioat_read_4 (struct ioat_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioat_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioat_submit_single (struct ioat_softc*) ; 
 scalar_t__ is_ioat_idle (scalar_t__) ; 

__attribute__((used)) static int
ioat_start_channel(struct ioat_softc *ioat)
{
	struct ioat_dma_hw_descriptor *hw_desc;
	struct ioat_descriptor *desc;
	struct bus_dmadesc *dmadesc;
	uint64_t status;
	uint32_t chanerr;
	int i;

	ioat_acquire(&ioat->dmaengine);

	/* Submit 'NULL' operation manually to avoid quiescing flag */
	desc = ioat_get_ring_entry(ioat, ioat->head);
	hw_desc = &ioat_get_descriptor(ioat, ioat->head)->dma;
	dmadesc = &desc->bus_dmadesc;

	dmadesc->callback_fn = NULL;
	dmadesc->callback_arg = NULL;

	hw_desc->u.control_raw = 0;
	hw_desc->u.control_generic.op = IOAT_OP_COPY;
	hw_desc->u.control_generic.completion_update = 1;
	hw_desc->size = 8;
	hw_desc->src_addr = 0;
	hw_desc->dest_addr = 0;
	hw_desc->u.control.null = 1;

	ioat_submit_single(ioat);
	ioat_release(&ioat->dmaengine);

	for (i = 0; i < 100; i++) {
		DELAY(1);
		status = ioat_get_chansts(ioat);
		if (is_ioat_idle(status))
			return (0);
	}

	chanerr = ioat_read_4(ioat, IOAT_CHANERR_OFFSET);
	ioat_log_message(0, "could not start channel: "
	    "status = %#jx error = %b\n", (uintmax_t)status, (int)chanerr,
	    IOAT_CHANERR_STR);
	return (ENXIO);
}