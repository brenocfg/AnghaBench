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
struct ida_softc {int /*<<< orphan*/  free_qcbs; } ;
struct ida_qcb {scalar_t__ error; int /*<<< orphan*/ * buf; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  sle; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCB_FREE ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct ida_qcb*,int /*<<< orphan*/ ) ; 
 TYPE_1__ link ; 

__attribute__((used)) static __inline void
ida_free_qcb(struct ida_softc *ida, struct ida_qcb *qcb)
{

	qcb->state = QCB_FREE;
	qcb->buf = NULL;
	qcb->error = 0;
	SLIST_INSERT_HEAD(&ida->free_qcbs, qcb, link.sle);
}