#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct aac_softc {scalar_t__ aac_commands; TYPE_4__* aac_queues; TYPE_2__** aac_qentries; TYPE_1__* aac_common; } ;
struct TYPE_8__ {int /*<<< orphan*/  XferState; } ;
struct aac_fib {scalar_t__ data; TYPE_3__ Header; } ;
struct aac_command {struct aac_fib* cm_fib; } ;
struct TYPE_10__ {scalar_t__ size; scalar_t__ notify; } ;
struct TYPE_9__ {scalar_t__** qt_qindex; } ;
struct TYPE_7__ {scalar_t__ aq_fib_size; int aq_fib_addr; } ;
struct TYPE_6__ {struct aac_fib* ac_fibs; } ;

/* Variables and functions */
 size_t AAC_CONSUMER_INDEX ; 
 scalar_t__ AAC_ERROR_NORMAL ; 
 int /*<<< orphan*/  AAC_FIBSTATE_DONEADAP ; 
#define  AAC_HOST_HIGH_CMD_QUEUE 131 
#define  AAC_HOST_HIGH_RESP_QUEUE 130 
#define  AAC_HOST_NORM_CMD_QUEUE 129 
#define  AAC_HOST_NORM_RESP_QUEUE 128 
 size_t AAC_PRODUCER_INDEX ; 
 int /*<<< orphan*/  AAC_QNOTIFY (struct aac_softc*,scalar_t__) ; 
 int ENOENT ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 TYPE_5__* aac_qinfo ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
aac_dequeue_fib(struct aac_softc *sc, int queue, u_int32_t *fib_size,
		struct aac_fib **fib_addr)
{
	u_int32_t pi, ci;
	u_int32_t fib_index;
	int error;
	int notify;

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	/* get the producer/consumer indices */
	pi = sc->aac_queues->qt_qindex[queue][AAC_PRODUCER_INDEX];
	ci = sc->aac_queues->qt_qindex[queue][AAC_CONSUMER_INDEX];

	/* check for queue empty */
	if (ci == pi) {
		error = ENOENT;
		goto out;
	}

	/* wrap the pi so the following test works */
	if (pi >= aac_qinfo[queue].size)
		pi = 0;

	notify = 0;
	if (ci == pi + 1)
		notify++;

	/* wrap the queue? */
	if (ci >= aac_qinfo[queue].size)
		ci = 0;

	/* fetch the entry */
	*fib_size = (sc->aac_qentries[queue] + ci)->aq_fib_size;

	switch (queue) {
	case AAC_HOST_NORM_CMD_QUEUE:
	case AAC_HOST_HIGH_CMD_QUEUE:
		/*
		 * The aq_fib_addr is only 32 bits wide so it can't be counted
		 * on to hold an address.  For AIF's, the adapter assumes
		 * that it's giving us an address into the array of AIF fibs.
		 * Therefore, we have to convert it to an index.
		 */
		fib_index = (sc->aac_qentries[queue] + ci)->aq_fib_addr /
			sizeof(struct aac_fib);
		*fib_addr = &sc->aac_common->ac_fibs[fib_index];
		break;

	case AAC_HOST_NORM_RESP_QUEUE:
	case AAC_HOST_HIGH_RESP_QUEUE:
	{
		struct aac_command *cm;

		/*
		 * As above, an index is used instead of an actual address.
		 * Gotta shift the index to account for the fast response
		 * bit.  No other correction is needed since this value was
		 * originally provided by the driver via the SenderFibAddress
		 * field.
		 */
		fib_index = (sc->aac_qentries[queue] + ci)->aq_fib_addr;
		cm = sc->aac_commands + (fib_index >> 2);
		*fib_addr = cm->cm_fib;

		/*
		 * Is this a fast response? If it is, update the fib fields in
		 * local memory since the whole fib isn't DMA'd back up.
		 */
		if (fib_index & 0x01) {
			(*fib_addr)->Header.XferState |= AAC_FIBSTATE_DONEADAP;
			*((u_int32_t*)((*fib_addr)->data)) = AAC_ERROR_NORMAL;
		}
		break;
	}
	default:
		panic("Invalid queue in aac_dequeue_fib()");
		break;
	}

	/* update consumer index */
	sc->aac_queues->qt_qindex[queue][AAC_CONSUMER_INDEX] = ci + 1;

	/* if we have made the queue un-full, notify the adapter */
	if (notify && (aac_qinfo[queue].notify != 0))
		AAC_QNOTIFY(sc, aac_qinfo[queue].notify);
	error = 0;

out:
	return(error);
}