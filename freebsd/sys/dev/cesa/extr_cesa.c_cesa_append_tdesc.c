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
struct cesa_tdma_desc {TYPE_1__* ctd_cthd; scalar_t__ ctd_cthd_paddr; } ;
struct cesa_request {int /*<<< orphan*/  cr_tdesc; } ;
struct TYPE_2__ {scalar_t__ cthd_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cesa_tdma_desc*,int /*<<< orphan*/ ) ; 
 struct cesa_tdma_desc* STAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cesa_tdma_desc ; 
 int /*<<< orphan*/  ctd_stq ; 

__attribute__((used)) static void
cesa_append_tdesc(struct cesa_request *cr, struct cesa_tdma_desc *ctd)
{
	struct cesa_tdma_desc *ctd_prev;

	if (!STAILQ_EMPTY(&cr->cr_tdesc)) {
		ctd_prev = STAILQ_LAST(&cr->cr_tdesc, cesa_tdma_desc, ctd_stq);
		ctd_prev->ctd_cthd->cthd_next = ctd->ctd_cthd_paddr;
	}

	ctd->ctd_cthd->cthd_next = 0;
	STAILQ_INSERT_TAIL(&cr->cr_tdesc, ctd, ctd_stq);
}