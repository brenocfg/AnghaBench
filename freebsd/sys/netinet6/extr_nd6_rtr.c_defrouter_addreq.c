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
struct sockaddr_in6 {int sin6_len; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_family; } ;
struct sockaddr {int dummy; } ;
struct rtentry {int dummy; } ;
struct nd_defrouter {int installed; TYPE_1__* ifp; int /*<<< orphan*/  rtaddr; } ;
typedef  int /*<<< orphan*/  mask ;
typedef  int /*<<< orphan*/  gate ;
typedef  int /*<<< orphan*/  def ;
struct TYPE_2__ {int /*<<< orphan*/  if_fib; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  RTFREE (struct rtentry*) ; 
 int /*<<< orphan*/  RTF_GATEWAY ; 
 int /*<<< orphan*/  RTM_ADD ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in6*,int) ; 
 int in6_rtrequest (int /*<<< orphan*/ ,struct sockaddr*,struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ ,struct rtentry**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd6_rtmsg (int /*<<< orphan*/ ,struct rtentry*) ; 

__attribute__((used)) static void
defrouter_addreq(struct nd_defrouter *new)
{
	struct sockaddr_in6 def, mask, gate;
	struct rtentry *newrt = NULL;
	int error;

	bzero(&def, sizeof(def));
	bzero(&mask, sizeof(mask));
	bzero(&gate, sizeof(gate));

	def.sin6_len = mask.sin6_len = gate.sin6_len =
	    sizeof(struct sockaddr_in6);
	def.sin6_family = gate.sin6_family = AF_INET6;
	gate.sin6_addr = new->rtaddr;

	error = in6_rtrequest(RTM_ADD, (struct sockaddr *)&def,
	    (struct sockaddr *)&gate, (struct sockaddr *)&mask,
	    RTF_GATEWAY, &newrt, new->ifp->if_fib);
	if (newrt) {
		nd6_rtmsg(RTM_ADD, newrt); /* tell user process */
		RTFREE(newrt);
	}
	if (error == 0)
		new->installed = 1;
}