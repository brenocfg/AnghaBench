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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  subtype ;
struct TYPE_2__ {int len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct lagg_port {int dummy; } ;
struct lacp_port {int dummy; } ;
struct ether_header {int dummy; } ;

/* Variables and functions */
 struct lacp_port* LACP_PORT (struct lagg_port*) ; 
#define  SLOWPROTOCOLS_SUBTYPE_LACP 129 
#define  SLOWPROTOCOLS_SUBTYPE_MARKER 128 
 int /*<<< orphan*/  lacp_marker_input (struct lacp_port*,struct mbuf*) ; 
 int /*<<< orphan*/  lacp_pdu_input (struct lacp_port*,struct mbuf*) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int,int,int*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

struct mbuf *
lacp_input(struct lagg_port *lgp, struct mbuf *m)
{
	struct lacp_port *lp = LACP_PORT(lgp);
	uint8_t subtype;

	if (m->m_pkthdr.len < sizeof(struct ether_header) + sizeof(subtype)) {
		m_freem(m);
		return (NULL);
	}

	m_copydata(m, sizeof(struct ether_header), sizeof(subtype), &subtype);
	switch (subtype) {
		case SLOWPROTOCOLS_SUBTYPE_LACP:
			lacp_pdu_input(lp, m);
			return (NULL);

		case SLOWPROTOCOLS_SUBTYPE_MARKER:
			lacp_marker_input(lp, m);
			return (NULL);
	}

	/* Not a subtype we are interested in */
	return (m);
}