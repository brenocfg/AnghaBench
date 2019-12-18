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
struct sctp_nat_msg {int dummy; } ;
struct sctp_nat_assoc {int state; } ;
struct libalias {int dummy; } ;

/* Variables and functions */
 int CL_process (struct libalias*,int,struct sctp_nat_assoc*,struct sctp_nat_msg*) ; 
 int ID_process (struct libalias*,int,struct sctp_nat_assoc*,struct sctp_nat_msg*) ; 
 int INa_process (struct libalias*,int,struct sctp_nat_assoc*,struct sctp_nat_msg*) ; 
 int INi_process (struct libalias*,int,struct sctp_nat_assoc*,struct sctp_nat_msg*) ; 
#define  SN_CL 132 
#define  SN_ID 131 
#define  SN_INa 130 
#define  SN_INi 129 
 int SN_NAT_PKT ; 
 int SN_PROCESSING_ERROR ; 
 int SN_RM ; 
#define  SN_UP 128 
 int UP_process (struct libalias*,int,struct sctp_nat_assoc*,struct sctp_nat_msg*) ; 

__attribute__((used)) static int
ProcessSctpMsg(struct libalias *la, int direction, struct sctp_nat_msg *sm, struct sctp_nat_assoc *assoc)
{
	int rtnval;

	switch (assoc->state) {
	case SN_ID: /* Idle */
		rtnval = ID_process(la, direction, assoc, sm);
		if (rtnval != SN_NAT_PKT) {
			assoc->state = SN_RM;/* Mark for removal*/
		}
		return (rtnval);
	case SN_INi: /* Initialising - Init */
		return (INi_process(la, direction, assoc, sm));
	case SN_INa: /* Initialising - AddIP */
		return (INa_process(la, direction, assoc, sm));
	case SN_UP:  /* Association UP */
		return (UP_process(la, direction, assoc, sm));
	case SN_CL:  /* Association Closing */
		return (CL_process(la, direction, assoc, sm));
	}
	return (SN_PROCESSING_ERROR);
}