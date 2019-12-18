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
struct socket {scalar_t__ so_type; TYPE_1__* so_proto; } ;
struct TYPE_2__ {scalar_t__ pr_protocol; } ;

/* Variables and functions */
 int EADDRINUSE ; 
 int EOPNOTSUPP ; 
 scalar_t__ IPPROTO_RSVP ; 
 scalar_t__ SOCK_RAW ; 
 int V_ip_rsvp_on ; 
 struct socket* V_ip_rsvpd ; 
 int /*<<< orphan*/  V_rsvp_on ; 

int
ip_rsvp_init(struct socket *so)
{

	if (so->so_type != SOCK_RAW ||
	    so->so_proto->pr_protocol != IPPROTO_RSVP)
		return EOPNOTSUPP;

	if (V_ip_rsvpd != NULL)
		return EADDRINUSE;

	V_ip_rsvpd = so;
	/*
	 * This may seem silly, but we need to be sure we don't over-increment
	 * the RSVP counter, in case something slips up.
	 */
	if (!V_ip_rsvp_on) {
		V_ip_rsvp_on = 1;
		V_rsvp_on++;
	}

	return 0;
}