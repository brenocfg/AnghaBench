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
struct libalias {int dummy; } ;
struct ip {int /*<<< orphan*/  ip_dst; int /*<<< orphan*/  ip_src; } ;
struct alias_data {int /*<<< orphan*/  maxpktsize; int /*<<< orphan*/  lnk; int /*<<< orphan*/ * aport; int /*<<< orphan*/ * sport; int /*<<< orphan*/ * dport; } ;

/* Variables and functions */
 int /*<<< orphan*/  AliasHandleRtspOut (struct libalias*,struct ip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FindRtspOut (struct libalias*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 scalar_t__ TFTP_PORT_NUMBER ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
protohandler(struct libalias *la, struct ip *pip, struct alias_data *ah)
{
	
	if (ntohs(*ah->dport) == TFTP_PORT_NUMBER)
		FindRtspOut(la, pip->ip_src, pip->ip_dst,
 			    *ah->sport, *ah->aport, IPPROTO_UDP);
	else AliasHandleRtspOut(la, pip, ah->lnk, ah->maxpktsize);	
	return (0);
}