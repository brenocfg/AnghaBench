#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u_int ;
typedef  scalar_t__ XENSTORE_RING_IDX ;
struct TYPE_5__ {scalar_t__ rsp_cons; scalar_t__ rsp_prod; int /*<<< orphan*/  rsp; } ;
struct TYPE_4__ {int /*<<< orphan*/  xen_intr_handle; int /*<<< orphan*/  ring_lock; } ;

/* Variables and functions */
 int EIO ; 
 int EWOULDBLOCK ; 
 int PCATCH ; 
 int PDROP ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 
 int msleep (TYPE_2__*,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  xen_intr_signal (int /*<<< orphan*/ ) ; 
 TYPE_2__* xen_store ; 
 TYPE_1__ xs ; 
 int /*<<< orphan*/  xs_check_indexes (scalar_t__,scalar_t__) ; 
 char* xs_get_input_chunk (scalar_t__,scalar_t__,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int
xs_read_store(void *tdata, unsigned len)
{
	XENSTORE_RING_IDX cons, prod;
	char *data = (char *)tdata;
	int error;

	while (len != 0) {
		u_int avail;
		const char *src;

		/* Hold lock so we can't miss wakeups should we block. */
		mtx_lock(&xs.ring_lock);
		cons = xen_store->rsp_cons;
		prod = xen_store->rsp_prod;
		if (cons == prod) {
			/*
			 * Nothing to read. Wait for a ring event.
			 *
			 * Note that the events from both queues
			 * are combined, so being woken does not
			 * guarantee that data exist in the read
			 * ring.
			 *
			 * To simplify error recovery and the retry,
			 * we specify PDROP so our lock is *not* held
			 * when msleep returns.
			 */
			error = msleep(xen_store, &xs.ring_lock, PCATCH|PDROP,
			    "xbread", /*timeout*/0);
			if (error && error != EWOULDBLOCK)
				return (error);
			continue;
		}
		mtx_unlock(&xs.ring_lock);

		/* Verify queue sanity. */
		if (!xs_check_indexes(cons, prod)) {
			xen_store->rsp_cons = xen_store->rsp_prod = 0;
			return (EIO);
		}

		src = xs_get_input_chunk(cons, prod, xen_store->rsp, &avail);
		if (avail > len)
			avail = len;

		/*
		 * Insure the data we read is related to the indexes
		 * we read above.
		 */
		rmb();

		memcpy(data, src, avail);
		data += avail;
		len -= avail;

		/*
		 * Insure that the producer of this ring does not see
		 * the ring space as free until after we have copied it
		 * out.
		 */
		mb();
		xen_store->rsp_cons += avail;

		/*
		 * xen_intr_signal() implies mb(). The producer will see
		 * the updated consumer index when the event is delivered.
		 */
		xen_intr_signal(xs.xen_intr_handle);
	}

	return (0);
}