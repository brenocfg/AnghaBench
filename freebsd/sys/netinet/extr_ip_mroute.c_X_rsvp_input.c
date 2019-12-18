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
 int /*<<< orphan*/  V_rsvp_on ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static int
X_rsvp_input(struct mbuf **mp, int *offp, int proto)
{
	struct mbuf *m;

	m = *mp;
	*mp = NULL;
	if (!V_rsvp_on)
		m_freem(m);
	return (IPPROTO_DONE);
}