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
struct pfctl {int /*<<< orphan*/  debug; int /*<<< orphan*/ * limit; int /*<<< orphan*/ * timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  PFFRAG_FRENT_HIWAT ; 
 int /*<<< orphan*/  PFR_KENTRY_HIWAT ; 
 int /*<<< orphan*/  PFSNODE_HIWAT ; 
 int /*<<< orphan*/  PFSTATE_ADAPT_END ; 
 int /*<<< orphan*/  PFSTATE_ADAPT_START ; 
 int /*<<< orphan*/  PFSTATE_HIWAT ; 
 size_t PFTM_ADAPTIVE_END ; 
 size_t PFTM_ADAPTIVE_START ; 
 size_t PFTM_FRAG ; 
 int /*<<< orphan*/  PFTM_FRAG_VAL ; 
 size_t PFTM_ICMP_ERROR_REPLY ; 
 int /*<<< orphan*/  PFTM_ICMP_ERROR_REPLY_VAL ; 
 size_t PFTM_ICMP_FIRST_PACKET ; 
 int /*<<< orphan*/  PFTM_ICMP_FIRST_PACKET_VAL ; 
 size_t PFTM_INTERVAL ; 
 int /*<<< orphan*/  PFTM_INTERVAL_VAL ; 
 size_t PFTM_OTHER_FIRST_PACKET ; 
 int /*<<< orphan*/  PFTM_OTHER_FIRST_PACKET_VAL ; 
 size_t PFTM_OTHER_MULTIPLE ; 
 int /*<<< orphan*/  PFTM_OTHER_MULTIPLE_VAL ; 
 size_t PFTM_OTHER_SINGLE ; 
 int /*<<< orphan*/  PFTM_OTHER_SINGLE_VAL ; 
 size_t PFTM_SRC_NODE ; 
 int /*<<< orphan*/  PFTM_SRC_NODE_VAL ; 
 size_t PFTM_TCP_CLOSED ; 
 int /*<<< orphan*/  PFTM_TCP_CLOSED_VAL ; 
 size_t PFTM_TCP_CLOSING ; 
 int /*<<< orphan*/  PFTM_TCP_CLOSING_VAL ; 
 size_t PFTM_TCP_ESTABLISHED ; 
 int /*<<< orphan*/  PFTM_TCP_ESTABLISHED_VAL ; 
 size_t PFTM_TCP_FIN_WAIT ; 
 int /*<<< orphan*/  PFTM_TCP_FIN_WAIT_VAL ; 
 size_t PFTM_TCP_FIRST_PACKET ; 
 int /*<<< orphan*/  PFTM_TCP_FIRST_PACKET_VAL ; 
 size_t PFTM_TCP_OPENING ; 
 int /*<<< orphan*/  PFTM_TCP_OPENING_VAL ; 
 size_t PFTM_TS_DIFF ; 
 int /*<<< orphan*/  PFTM_TS_DIFF_VAL ; 
 size_t PFTM_UDP_FIRST_PACKET ; 
 int /*<<< orphan*/  PFTM_UDP_FIRST_PACKET_VAL ; 
 size_t PFTM_UDP_MULTIPLE ; 
 int /*<<< orphan*/  PFTM_UDP_MULTIPLE_VAL ; 
 size_t PFTM_UDP_SINGLE ; 
 int /*<<< orphan*/  PFTM_UDP_SINGLE_VAL ; 
 int /*<<< orphan*/  PF_DEBUG_URGENT ; 
 size_t PF_LIMIT_FRAGS ; 
 size_t PF_LIMIT_SRC_NODES ; 
 size_t PF_LIMIT_STATES ; 
 size_t PF_LIMIT_TABLE_ENTRIES ; 

void
pfctl_init_options(struct pfctl *pf)
{

	pf->timeout[PFTM_TCP_FIRST_PACKET] = PFTM_TCP_FIRST_PACKET_VAL;
	pf->timeout[PFTM_TCP_OPENING] = PFTM_TCP_OPENING_VAL;
	pf->timeout[PFTM_TCP_ESTABLISHED] = PFTM_TCP_ESTABLISHED_VAL;
	pf->timeout[PFTM_TCP_CLOSING] = PFTM_TCP_CLOSING_VAL;
	pf->timeout[PFTM_TCP_FIN_WAIT] = PFTM_TCP_FIN_WAIT_VAL;
	pf->timeout[PFTM_TCP_CLOSED] = PFTM_TCP_CLOSED_VAL;
	pf->timeout[PFTM_UDP_FIRST_PACKET] = PFTM_UDP_FIRST_PACKET_VAL;
	pf->timeout[PFTM_UDP_SINGLE] = PFTM_UDP_SINGLE_VAL;
	pf->timeout[PFTM_UDP_MULTIPLE] = PFTM_UDP_MULTIPLE_VAL;
	pf->timeout[PFTM_ICMP_FIRST_PACKET] = PFTM_ICMP_FIRST_PACKET_VAL;
	pf->timeout[PFTM_ICMP_ERROR_REPLY] = PFTM_ICMP_ERROR_REPLY_VAL;
	pf->timeout[PFTM_OTHER_FIRST_PACKET] = PFTM_OTHER_FIRST_PACKET_VAL;
	pf->timeout[PFTM_OTHER_SINGLE] = PFTM_OTHER_SINGLE_VAL;
	pf->timeout[PFTM_OTHER_MULTIPLE] = PFTM_OTHER_MULTIPLE_VAL;
	pf->timeout[PFTM_FRAG] = PFTM_FRAG_VAL;
	pf->timeout[PFTM_INTERVAL] = PFTM_INTERVAL_VAL;
	pf->timeout[PFTM_SRC_NODE] = PFTM_SRC_NODE_VAL;
	pf->timeout[PFTM_TS_DIFF] = PFTM_TS_DIFF_VAL;
	pf->timeout[PFTM_ADAPTIVE_START] = PFSTATE_ADAPT_START;
	pf->timeout[PFTM_ADAPTIVE_END] = PFSTATE_ADAPT_END;

	pf->limit[PF_LIMIT_STATES] = PFSTATE_HIWAT;
	pf->limit[PF_LIMIT_FRAGS] = PFFRAG_FRENT_HIWAT;
	pf->limit[PF_LIMIT_SRC_NODES] = PFSNODE_HIWAT;
	pf->limit[PF_LIMIT_TABLE_ENTRIES] = PFR_KENTRY_HIWAT;

	pf->debug = PF_DEBUG_URGENT;
}