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
struct icl_pdu {int /*<<< orphan*/  ip_data_mbuf; int /*<<< orphan*/  ip_ahs_mbuf; int /*<<< orphan*/  ip_bhs_mbuf; } ;
struct icl_conn {int /*<<< orphan*/  ic_outstanding_pdus; } ;

/* Variables and functions */
 int /*<<< orphan*/  icl_pdu_zone ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct icl_pdu*) ; 

__attribute__((used)) static void
icl_soft_conn_pdu_free(struct icl_conn *ic, struct icl_pdu *ip)
{

	m_freem(ip->ip_bhs_mbuf);
	m_freem(ip->ip_ahs_mbuf);
	m_freem(ip->ip_data_mbuf);
	uma_zfree(icl_pdu_zone, ip);
#ifdef DIAGNOSTIC
	refcount_release(&ic->ic_outstanding_pdus);
#endif
}