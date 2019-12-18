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
struct xencons_priv {char* rbuf; int /*<<< orphan*/  rp; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int (* read ) (struct xencons_priv*,char*,int) ;} ;

/* Variables and functions */
 size_t RBUF_MASK (int /*<<< orphan*/ ) ; 
 int stub1 (struct xencons_priv*,char*,int) ; 
 int /*<<< orphan*/  xencons_lock (struct xencons_priv*) ; 
 int /*<<< orphan*/  xencons_unlock (struct xencons_priv*) ; 

__attribute__((used)) static void
xencons_rx(struct xencons_priv *cons)
{
	char buf[16];
	int sz;

	xencons_lock(cons);
	while ((sz = cons->ops->read(cons, buf, sizeof(buf))) > 0) {
		int i;

		for (i = 0; i < sz; i++)
			cons->rbuf[RBUF_MASK(cons->rp++)] = buf[i];
	}
	xencons_unlock(cons);
}