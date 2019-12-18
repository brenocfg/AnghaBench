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
struct xencons_priv {scalar_t__ rp; scalar_t__ rc; scalar_t__* rbuf; } ;

/* Variables and functions */
 size_t RBUF_MASK (scalar_t__) ; 
 int /*<<< orphan*/  xencons_lock (struct xencons_priv*) ; 
 int /*<<< orphan*/  xencons_unlock (struct xencons_priv*) ; 

__attribute__((used)) static int
xencons_getc(struct xencons_priv *cons)
{
	int ret;

	xencons_lock(cons);
	if (cons->rp != cons->rc) {
		/* We need to return only one char */
		ret = (int)cons->rbuf[RBUF_MASK(cons->rc)];
		cons->rc++;
	} else {
		ret = -1;
	}

	xencons_unlock(cons);

	return (ret);
}