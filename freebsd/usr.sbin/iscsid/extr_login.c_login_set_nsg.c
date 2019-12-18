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
struct pdu {scalar_t__ pdu_bhs; } ;
struct iscsi_bhs_login_request {int bhslr_flags; } ;

/* Variables and functions */
 int BHSLR_STAGE_FULL_FEATURE_PHASE ; 
 int BHSLR_STAGE_OPERATIONAL_NEGOTIATION ; 
 int BHSLR_STAGE_SECURITY_NEGOTIATION ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
login_set_nsg(struct pdu *request, int nsg)
{
	struct iscsi_bhs_login_request *bhslr;

	assert(nsg == BHSLR_STAGE_SECURITY_NEGOTIATION ||
	    nsg == BHSLR_STAGE_OPERATIONAL_NEGOTIATION ||
	    nsg == BHSLR_STAGE_FULL_FEATURE_PHASE);

	bhslr = (struct iscsi_bhs_login_request *)request->pdu_bhs;

	bhslr->bhslr_flags &= 0xFC;
	bhslr->bhslr_flags |= nsg;
}