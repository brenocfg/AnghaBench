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
typedef  void* u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct ip_print_demux_state {scalar_t__ advance; void* nh; scalar_t__ off; void* len; int /*<<< orphan*/  const* cp; struct ip const* ip; } ;
struct ip {int dummy; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ip_print_demux (int /*<<< orphan*/ *,struct ip_print_demux_state*) ; 

void
ip_print_inner(netdissect_options *ndo,
	       const u_char *bp,
	       u_int length, u_int nh,
	       const u_char *bp2)
{
	struct ip_print_demux_state  ipd;

	ipd.ip = (const struct ip *)bp2;
	ipd.cp = bp;
	ipd.len  = length;
	ipd.off  = 0;
	ipd.nh   = nh;
	ipd.advance = 0;

	ip_print_demux(ndo, &ipd);
}