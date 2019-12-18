#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int error; int transferred; } ;
typedef  TYPE_1__ xdma_transfer_status_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct xdma_channel {int dummy; } ;
struct softdma_softc {int dummy; } ;
struct softdma_desc {int control; scalar_t__ direction; struct softdma_desc* next; } ;
struct softdma_channel {size_t idx_tail; int /*<<< orphan*/  descs_used_count; struct softdma_desc* descs; struct xdma_channel* xchan; struct softdma_softc* sc; } ;

/* Variables and functions */
 int CONTROL_OWN ; 
 scalar_t__ XDMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 
 size_t softdma_next_desc (struct softdma_channel*,size_t) ; 
 int softdma_process_rx (struct softdma_channel*,struct softdma_desc*) ; 
 int softdma_process_tx (struct softdma_channel*,struct softdma_desc*) ; 
 int /*<<< orphan*/  xchan_seg_done (struct xdma_channel*,TYPE_1__*) ; 

__attribute__((used)) static uint32_t
softdma_process_descriptors(struct softdma_channel *chan,
    xdma_transfer_status_t *status)
{
	struct xdma_channel *xchan;
	struct softdma_desc *desc;
	struct softdma_softc *sc;
	xdma_transfer_status_t st;
	int ret;

	sc = chan->sc;

	xchan = chan->xchan;

	desc = &chan->descs[chan->idx_tail];

	while (desc != NULL) {

		if ((desc->control & CONTROL_OWN) == 0) {
			break;
		}

		if (desc->direction == XDMA_MEM_TO_DEV) {
			ret = softdma_process_tx(chan, desc);
		} else {
			ret = softdma_process_rx(chan, desc);
			if (ret == 0) {
				/* No new data available. */
				break;
			}
		}

		/* Descriptor processed. */
		desc->control = 0;

		if (ret >= 0) {
			st.error = 0;
			st.transferred = ret;
		} else {
			st.error = ret;
			st.transferred = 0;
		}

		xchan_seg_done(xchan, &st);
		atomic_subtract_int(&chan->descs_used_count, 1);

		if (ret >= 0) {
			status->transferred += ret;
		} else {
			status->error = 1;
			break;
		}

		chan->idx_tail = softdma_next_desc(chan, chan->idx_tail);

		/* Process next descriptor, if any. */
		desc = desc->next;
	}

	return (0);
}