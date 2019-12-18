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
struct icl_pdu {int /*<<< orphan*/  ip_data_mbuf; } ;
struct icl_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_copydata (int /*<<< orphan*/ ,size_t,size_t,void*) ; 

void
icl_soft_conn_pdu_get_data(struct icl_conn *ic, struct icl_pdu *ip,
    size_t off, void *addr, size_t len)
{

	m_copydata(ip->ip_data_mbuf, off, len, addr);
}