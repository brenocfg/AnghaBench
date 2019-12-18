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
typedef  size_t u_int ;
struct nm_bdg_kthread {size_t qfirst; size_t qlast; TYPE_1__* bps; } ;
struct netmap_kring {int /*<<< orphan*/  (* nm_notify ) (struct netmap_kring*,int /*<<< orphan*/ ) ;} ;
struct netmap_bwrap_adapter {int /*<<< orphan*/  hwna; } ;
struct TYPE_2__ {struct netmap_bwrap_adapter* bna; } ;

/* Variables and functions */
 struct netmap_kring** NMR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NR_RX ; 
 int /*<<< orphan*/  stub1 (struct netmap_kring*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
netmap_bwrap_polling(void *data)
{
	struct nm_bdg_kthread *nbk = data;
	struct netmap_bwrap_adapter *bna;
	u_int qfirst, qlast, i;
	struct netmap_kring **kring0, *kring;

	if (!nbk)
		return;
	qfirst = nbk->qfirst;
	qlast = nbk->qlast;
	bna = nbk->bps->bna;
	kring0 = NMR(bna->hwna, NR_RX);

	for (i = qfirst; i < qlast; i++) {
		kring = kring0[i];
		kring->nm_notify(kring, 0);
	}
}