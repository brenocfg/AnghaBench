#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rt_msghdr {int /*<<< orphan*/  rtm_type; } ;
struct rt_addrinfo {int dummy; } ;
struct TYPE_3__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 TYPE_1__* INFO_GATE (struct rt_addrinfo*) ; 
 int /*<<< orphan*/  S_ADDR (TYPE_1__*) ; 
 int /*<<< orphan*/  age (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdisc_age (int /*<<< orphan*/ ) ; 
 scalar_t__ rdisc_ok ; 
 int /*<<< orphan*/  rtm_type_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_act (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rtm_lose(struct rt_msghdr *rtm,
	 struct rt_addrinfo *info)
{
	if (INFO_GATE(info) == 0
	    || INFO_GATE(info)->sa_family != AF_INET) {
		trace_act("ignore %s without gateway",
			  rtm_type_name(rtm->rtm_type));
		return;
	}

	if (rdisc_ok)
		rdisc_age(S_ADDR(INFO_GATE(info)));
	age(S_ADDR(INFO_GATE(info)));
}