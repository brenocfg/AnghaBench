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
struct ida_req {int dummy; } ;
struct ida_qcb {int /*<<< orphan*/  hwqcb; } ;
struct ida_hdr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sle; } ;

/* Variables and functions */
 struct ida_qcb* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ link ; 

__attribute__((used)) static __inline struct ida_qcb *
ida_get_qcb(struct ida_softc *ida)
{
	struct ida_qcb *qcb;

	if ((qcb = SLIST_FIRST(&ida->free_qcbs)) != NULL) {
		SLIST_REMOVE_HEAD(&ida->free_qcbs, link.sle);
		bzero(qcb->hwqcb, sizeof(struct ida_hdr) + sizeof(struct ida_req));
	}
	return (qcb);
}