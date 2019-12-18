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
struct in6_aliasreq {int /*<<< orphan*/  ifra_dstaddr; int /*<<< orphan*/  ifra_addr; int /*<<< orphan*/  ifra_name; } ;
struct addrinfo {TYPE_1__* ai_addr; } ;
typedef  int /*<<< orphan*/  in6_addreq ;
struct TYPE_2__ {int /*<<< orphan*/  sa_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCSIFPHYADDR_IN6 ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct in6_aliasreq*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct in6_aliasreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void
in6_set_tunnel(int s, struct addrinfo *srcres, struct addrinfo *dstres)
{
	struct in6_aliasreq in6_addreq; 

	memset(&in6_addreq, 0, sizeof(in6_addreq));
	strlcpy(in6_addreq.ifra_name, name, sizeof(in6_addreq.ifra_name));
	memcpy(&in6_addreq.ifra_addr, srcres->ai_addr, srcres->ai_addr->sa_len);
	memcpy(&in6_addreq.ifra_dstaddr, dstres->ai_addr,
	    dstres->ai_addr->sa_len);

	if (ioctl(s, SIOCSIFPHYADDR_IN6, &in6_addreq) < 0)
		warn("SIOCSIFPHYADDR_IN6");
}