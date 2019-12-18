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
struct ida_softc {int flags; int /*<<< orphan*/  buffer_dmat; } ;
struct ida_qcb {int /*<<< orphan*/  dmamap; } ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int BUS_DMA_NOWAIT ; 
 int BUS_DMA_WAITOK ; 
 int EINPROGRESS ; 
 int IDA_INTERRUPTS ; 
 int IDA_QFROZEN ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ida_qcb*,int) ; 
 int /*<<< orphan*/  ida_data_cb ; 

__attribute__((used)) static int
ida_map_qcb(struct ida_softc *ida, struct ida_qcb *qcb, void *data,
    bus_size_t datasize)
{
	int error, flags;

	if (ida->flags & IDA_INTERRUPTS)
		flags = BUS_DMA_WAITOK;
	else
		flags = BUS_DMA_NOWAIT;
	error = bus_dmamap_load(ida->buffer_dmat, qcb->dmamap, data, datasize,
	    ida_data_cb, qcb, flags);
	if (error == EINPROGRESS) {
		ida->flags |= IDA_QFROZEN;
		error = 0;
	}
	return (error);
}