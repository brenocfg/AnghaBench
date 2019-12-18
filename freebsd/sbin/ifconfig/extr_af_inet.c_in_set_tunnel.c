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
struct in_aliasreq {int /*<<< orphan*/  ifra_dstaddr; int /*<<< orphan*/  ifra_addr; int /*<<< orphan*/  ifra_name; } ;
struct addrinfo {TYPE_1__* ai_addr; } ;
typedef  int /*<<< orphan*/  addreq ;
struct TYPE_2__ {int /*<<< orphan*/  sa_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  SIOCSIFPHYADDR ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct in_aliasreq*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct in_aliasreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void
in_set_tunnel(int s, struct addrinfo *srcres, struct addrinfo *dstres)
{
	struct in_aliasreq addreq;

	memset(&addreq, 0, sizeof(addreq));
	strlcpy(addreq.ifra_name, name, IFNAMSIZ);
	memcpy(&addreq.ifra_addr, srcres->ai_addr, srcres->ai_addr->sa_len);
	memcpy(&addreq.ifra_dstaddr, dstres->ai_addr, dstres->ai_addr->sa_len);

	if (ioctl(s, SIOCSIFPHYADDR, &addreq) < 0)
		warn("SIOCSIFPHYADDR");
}