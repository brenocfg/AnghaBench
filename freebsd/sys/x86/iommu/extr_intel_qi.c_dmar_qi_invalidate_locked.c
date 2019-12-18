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
struct dmar_unit {int dummy; } ;
struct dmar_qi_genseq {int dummy; } ;
struct dmar_domain {int /*<<< orphan*/  domain; struct dmar_unit* dmar; } ;
typedef  int dmar_gaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_ASSERT_LOCKED (struct dmar_unit*) ; 
 int DMAR_IQ_DESCR_IOTLB_DID (int /*<<< orphan*/ ) ; 
 int DMAR_IQ_DESCR_IOTLB_DR ; 
 int DMAR_IQ_DESCR_IOTLB_DW ; 
 int DMAR_IQ_DESCR_IOTLB_INV ; 
 int DMAR_IQ_DESCR_IOTLB_PAGE ; 
 int calc_am (struct dmar_unit*,int,int,int*) ; 
 int /*<<< orphan*/  dmar_qi_advance_tail (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_qi_emit (struct dmar_unit*,int,int) ; 
 int /*<<< orphan*/  dmar_qi_emit_wait_seq (struct dmar_unit*,struct dmar_qi_genseq*,int) ; 
 int /*<<< orphan*/  dmar_qi_ensure (struct dmar_unit*,int) ; 

void
dmar_qi_invalidate_locked(struct dmar_domain *domain, dmar_gaddr_t base,
    dmar_gaddr_t size, struct dmar_qi_genseq *pseq, bool emit_wait)
{
	struct dmar_unit *unit;
	dmar_gaddr_t isize;
	int am;

	unit = domain->dmar;
	DMAR_ASSERT_LOCKED(unit);
	for (; size > 0; base += isize, size -= isize) {
		am = calc_am(unit, base, size, &isize);
		dmar_qi_ensure(unit, 1);
		dmar_qi_emit(unit, DMAR_IQ_DESCR_IOTLB_INV |
		    DMAR_IQ_DESCR_IOTLB_PAGE | DMAR_IQ_DESCR_IOTLB_DW |
		    DMAR_IQ_DESCR_IOTLB_DR |
		    DMAR_IQ_DESCR_IOTLB_DID(domain->domain),
		    base | am);
	}
	dmar_qi_emit_wait_seq(unit, pseq, emit_wait);
	dmar_qi_advance_tail(unit);
}