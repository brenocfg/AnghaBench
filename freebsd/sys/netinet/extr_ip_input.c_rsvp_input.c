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
struct mbuf {int dummy; } ;

/* Variables and functions */
 int IPPROTO_DONE ; 
 int /*<<< orphan*/ * V_ip_rsvpd ; 
 int /*<<< orphan*/  V_rsvp_on ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  rip_input (struct mbuf**,int*,int) ; 
 int /*<<< orphan*/  rsvp_input_p (struct mbuf**,int*,int) ; 

int
rsvp_input(struct mbuf **mp, int *offp, int proto)
{
	struct mbuf *m;

	m = *mp;
	*mp = NULL;

	if (rsvp_input_p) { /* call the real one if loaded */
		*mp = m;
		rsvp_input_p(mp, offp, proto);
		return (IPPROTO_DONE);
	}

	/* Can still get packets with rsvp_on = 0 if there is a local member
	 * of the group to which the RSVP packet is addressed.  But in this
	 * case we want to throw the packet away.
	 */
	
	if (!V_rsvp_on) {
		m_freem(m);
		return (IPPROTO_DONE);
	}

	if (V_ip_rsvpd != NULL) { 
		*mp = m;
		rip_input(mp, offp, proto);
		return (IPPROTO_DONE);
	}
	/* Drop the packet */
	m_freem(m);
	return (IPPROTO_DONE);
}