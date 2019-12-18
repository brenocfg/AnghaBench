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
struct TYPE_5__ {scalar_t__ req_cons; scalar_t__ req_prod; int /*<<< orphan*/  req; } ;
struct TYPE_4__ {int /*<<< orphan*/  xen_intr_handle; int /*<<< orphan*/  ring_lock; int /*<<< orphan*/  request_mutex; } ;

/* Variables and functions */
 int EIO ; 
 int EWOULDBLOCK ; 
 int PCATCH ; 
 int PDROP ; 
 int /*<<< orphan*/  SX_XLOCKED ; 
 scalar_t__ XENSTORE_RING_SIZE ; 
 int /*<<< orphan*/  memcpy (void*,char const*,unsigned int) ; 
 int msleep (TYPE_2__*,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  xen_intr_signal (int /*<<< orphan*/ ) ; 
 TYPE_2__* xen_store ; 
 TYPE_1__ xs ; 
 int /*<<< orphan*/  xs_check_indexes (scalar_t__,scalar_t__) ; 
 void* xs_get_output_chunk (scalar_t__,scalar_t__,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int
xs_write_store(const void *tdata, unsigned len)
{
	XENSTORE_RING_IDX cons, prod;
	const char *data = (const char *)tdata;
	int error;

	sx_assert(&xs.request_mutex, SX_XLOCKED);
	while (len != 0) {
		void *dst;
		u_int avail;

		/* Hold lock so we can't miss wakeups should we block. */
		mtx_lock(&xs.ring_lock);
		cons = xen_store->req_cons;
		prod = xen_store->req_prod;
		if ((prod - cons) == XENSTORE_RING_SIZE) {
			/*
			 * Output ring is full. Wait for a ring event.
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
			     "xbwrite", /*timeout*/0);
			if (error && error != EWOULDBLOCK)
				return (error);

			/* Try again. */
			continue;
		}
		mtx_unlock(&xs.ring_lock);

		/* Verify queue sanity. */
		if (!xs_check_indexes(cons, prod)) {
			xen_store->req_cons = xen_store->req_prod = 0;
			return (EIO);
		}

		dst = xs_get_output_chunk(cons, prod, xen_store->req, &avail);
		if (avail > len)
			avail = len;

		memcpy(dst, data, avail);
		data += avail;
		len -= avail;

		/*
		 * The store to the producer index, which indicates
		 * to the other side that new data has arrived, must
		 * be visible only after our copy of the data into the
		 * ring has completed.
		 */
		wmb();
		xen_store->req_prod += avail;

		/*
		 * xen_intr_signal() implies mb(). The other side will see
		 * the change to req_prod at the time of the interrupt.
		 */
		xen_intr_signal(xs.xen_intr_handle);
	}

	return (0);
}