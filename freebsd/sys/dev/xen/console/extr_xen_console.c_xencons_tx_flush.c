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
struct xencons_priv {scalar_t__ wc; scalar_t__ wp; int /*<<< orphan*/ * wbuf; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* write ) (struct xencons_priv*,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 size_t WBUF_MASK (int) ; 
 int WBUF_SIZE ; 
 scalar_t__ __predict_false (int) ; 
 scalar_t__ __predict_true (int) ; 
 int stub1 (struct xencons_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xencons_lock (struct xencons_priv*) ; 
 int /*<<< orphan*/  xencons_unlock (struct xencons_priv*) ; 

__attribute__((used)) static void
xencons_tx_flush(struct xencons_priv *cons, int force)
{
	int        sz;

	xencons_lock(cons);
	while (cons->wc != cons->wp) {
		int sent;
		sz = cons->wp - cons->wc;
		if (sz > (WBUF_SIZE - WBUF_MASK(cons->wc)))
			sz = WBUF_SIZE - WBUF_MASK(cons->wc);
		sent = cons->ops->write(cons, &cons->wbuf[WBUF_MASK(cons->wc)],
		    sz);

		/*
		 * The other end may not have been initialized. Ignore
		 * the force.
		 */
		if (__predict_false(sent < 0))
			break;

		/*
		 * If force is set, spin until the console data is
		 * flushed through the domain controller.
		 */
		if (sent == 0 && __predict_true(!force))
			break;

		cons->wc += sent;
	}
	xencons_unlock(cons);
}