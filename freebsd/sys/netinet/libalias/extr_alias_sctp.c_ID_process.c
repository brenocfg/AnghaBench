#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* Init; } ;
struct sctp_nat_msg {int msg; TYPE_4__* ip_hdr; TYPE_3__ sctpchnk; TYPE_1__* sctp_hdr; } ;
struct sctp_nat_assoc {int /*<<< orphan*/  exp; int /*<<< orphan*/  state; int /*<<< orphan*/  TableRegister; int /*<<< orphan*/  l_vtag; int /*<<< orphan*/  g_port; int /*<<< orphan*/  l_port; int /*<<< orphan*/  a_addr; int /*<<< orphan*/  l_addr; int /*<<< orphan*/  g_vtag; } ;
struct libalias {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  ip_src; int /*<<< orphan*/  ip_dst; } ;
struct TYPE_6__ {int /*<<< orphan*/  initiate_tag; } ;
struct TYPE_5__ {int /*<<< orphan*/  src_port; int /*<<< orphan*/  dest_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddGlobalIPAddresses (struct sctp_nat_msg*,struct sctp_nat_assoc*,int) ; 
 int /*<<< orphan*/  AddSctpAssocGlobal (struct libalias*,struct sctp_nat_assoc*) ; 
 int /*<<< orphan*/  AddSctpAssocLocal (struct libalias*,struct sctp_nat_assoc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FindAliasAddress (struct libalias*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FindSctpRedirectAddress (struct libalias*,struct sctp_nat_msg*) ; 
 int /*<<< orphan*/  GetAsconfVtags (struct libalias*,struct sctp_nat_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int SN_DROP_PKT ; 
 int /*<<< orphan*/  SN_INa ; 
 int /*<<< orphan*/  SN_INi ; 
 int /*<<< orphan*/  SN_I_T (struct libalias*) ; 
 int SN_NAT_PKT ; 
 int SN_REPLY_ABORT ; 
 int SN_REPLY_ERROR ; 
#define  SN_SCTP_ASCONF 131 
#define  SN_SCTP_INIT 130 
#define  SN_TO_GLOBAL 129 
#define  SN_TO_LOCAL 128 
 int /*<<< orphan*/  SN_WAIT_TOGLOBAL ; 
 int /*<<< orphan*/  SN_WAIT_TOLOCAL ; 
 int /*<<< orphan*/  sctp_AddTimeOut (struct libalias*,struct sctp_nat_assoc*) ; 
 int /*<<< orphan*/  sysctl_accept_global_ootb_addip ; 
 int /*<<< orphan*/  sysctl_track_global_addresses ; 

__attribute__((used)) static int
ID_process(struct libalias *la, int direction, struct sctp_nat_assoc *assoc, struct sctp_nat_msg *sm)
{
	switch (sm->msg) {
	case SN_SCTP_ASCONF:           /* a packet containing an ASCONF chunk with ADDIP */
		if (!sysctl_accept_global_ootb_addip && (direction == SN_TO_LOCAL))
			return (SN_DROP_PKT);
		/* if this Asconf packet does not contain the Vtag parameters it is of no use in Idle state */
		if (!GetAsconfVtags(la, sm, &(assoc->l_vtag), &(assoc->g_vtag), direction))
			return (SN_DROP_PKT);
		/* FALLTHROUGH */
	case SN_SCTP_INIT:            /* a packet containing an INIT chunk or an ASCONF AddIP */
		if (sysctl_track_global_addresses)
			AddGlobalIPAddresses(sm, assoc, direction);
		switch (direction) {
		case SN_TO_GLOBAL:
			assoc->l_addr = sm->ip_hdr->ip_src;
			assoc->a_addr = FindAliasAddress(la, assoc->l_addr);
			assoc->l_port = sm->sctp_hdr->src_port;
			assoc->g_port = sm->sctp_hdr->dest_port;
			if (sm->msg == SN_SCTP_INIT)
				assoc->g_vtag = sm->sctpchnk.Init->initiate_tag;
			if (AddSctpAssocGlobal(la, assoc)) /* DB clash *///**** need to add dst address
				return ((sm->msg == SN_SCTP_INIT) ? SN_REPLY_ABORT : SN_REPLY_ERROR);
			if (sm->msg == SN_SCTP_ASCONF) {
				if (AddSctpAssocLocal(la, assoc, sm->ip_hdr->ip_dst)) /* DB clash */
					return (SN_REPLY_ERROR);
				assoc->TableRegister |= SN_WAIT_TOLOCAL; /* wait for tolocal ack */
			}
		break;
		case SN_TO_LOCAL:
			assoc->l_addr = FindSctpRedirectAddress(la, sm);
			assoc->a_addr = sm->ip_hdr->ip_dst;
			assoc->l_port = sm->sctp_hdr->dest_port;
			assoc->g_port = sm->sctp_hdr->src_port;
			if (sm->msg == SN_SCTP_INIT)
				assoc->l_vtag = sm->sctpchnk.Init->initiate_tag;
			if (AddSctpAssocLocal(la, assoc, sm->ip_hdr->ip_src)) /* DB clash */
				return ((sm->msg == SN_SCTP_INIT) ? SN_REPLY_ABORT : SN_REPLY_ERROR);
			if (sm->msg == SN_SCTP_ASCONF) {
				if (AddSctpAssocGlobal(la, assoc)) /* DB clash */ //**** need to add src address
					return (SN_REPLY_ERROR);
				assoc->TableRegister |= SN_WAIT_TOGLOBAL; /* wait for toglobal ack */
					}
			break;
		}
		assoc->state = (sm->msg == SN_SCTP_INIT) ? SN_INi : SN_INa;
		assoc->exp = SN_I_T(la);
		sctp_AddTimeOut(la,assoc);
		return (SN_NAT_PKT);
	default: /* Any other type of SCTP message is not valid in Idle */
		return (SN_DROP_PKT);
	}
	return (SN_DROP_PKT);/* shouldn't get here very bad: log, drop and hope for the best */
}