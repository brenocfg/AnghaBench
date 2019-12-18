#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* Init; } ;
struct sctp_nat_msg {int msg; TYPE_3__ sctpchnk; TYPE_1__* ip_hdr; } ;
struct sctp_nat_assoc {void* state; int /*<<< orphan*/  g_vtag; int /*<<< orphan*/  l_addr; int /*<<< orphan*/  l_vtag; int /*<<< orphan*/  num_Gaddr; } ;
struct libalias {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  initiate_tag; } ;
struct TYPE_4__ {int /*<<< orphan*/  ip_src; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddGlobalIPAddresses (struct sctp_nat_msg*,struct sctp_nat_assoc*,int) ; 
 int /*<<< orphan*/  AddSctpAssocGlobal (struct libalias*,struct sctp_nat_assoc*) ; 
 int /*<<< orphan*/  AddSctpAssocLocal (struct libalias*,struct sctp_nat_assoc*,int /*<<< orphan*/ ) ; 
 int SN_DROP_PKT ; 
 int /*<<< orphan*/  SN_I_T (struct libalias*) ; 
 int SN_NAT_PKT ; 
 void* SN_RM ; 
#define  SN_SCTP_ABORT 132 
#define  SN_SCTP_INIT 131 
#define  SN_SCTP_INITACK 130 
 int SN_SEND_ABORT ; 
#define  SN_TO_GLOBAL 129 
#define  SN_TO_LOCAL 128 
 void* SN_UP ; 
 int /*<<< orphan*/  SN_U_T (struct libalias*) ; 
 int /*<<< orphan*/  sctp_ResetTimeOut (struct libalias*,struct sctp_nat_assoc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
INi_process(struct libalias *la, int direction, struct sctp_nat_assoc *assoc, struct sctp_nat_msg *sm)
{
	switch (sm->msg) {
	case SN_SCTP_INIT:            /* a packet containing a retransmitted INIT chunk */
		sctp_ResetTimeOut(la, assoc, SN_I_T(la));
		return (SN_NAT_PKT);
	case SN_SCTP_INITACK:         /* a packet containing an INIT-ACK chunk */
		switch (direction) {
		case SN_TO_LOCAL:
			if (assoc->num_Gaddr) /*If tracking global addresses for this association */
				AddGlobalIPAddresses(sm, assoc, direction);
			assoc->l_vtag = sm->sctpchnk.Init->initiate_tag;
			if (AddSctpAssocLocal(la, assoc, sm->ip_hdr->ip_src)) { /* DB clash */
				assoc->state = SN_RM;/* Mark for removal*/
				return (SN_SEND_ABORT);
			}
			break;
		case SN_TO_GLOBAL:
			assoc->l_addr = sm->ip_hdr->ip_src; // Only if not set in Init! *
			assoc->g_vtag = sm->sctpchnk.Init->initiate_tag;
			if (AddSctpAssocGlobal(la, assoc)) { /* DB clash */
				assoc->state = SN_RM;/* Mark for removal*/
				return (SN_SEND_ABORT);
			}
			break;
		}
		assoc->state = SN_UP;/* association established for NAT */
		sctp_ResetTimeOut(la,assoc, SN_U_T(la));
		return (SN_NAT_PKT);
	case SN_SCTP_ABORT:           /* a packet containing an ABORT chunk */
		assoc->state = SN_RM;/* Mark for removal*/
		return (SN_NAT_PKT);
	default:
		return (SN_DROP_PKT);
	}
	return (SN_DROP_PKT);/* shouldn't get here very bad: log, drop and hope for the best */
}