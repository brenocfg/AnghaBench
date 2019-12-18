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
struct ip {int /*<<< orphan*/  ip_src; } ;
struct alias_data {int /*<<< orphan*/  aport; int /*<<< orphan*/  aaddr; int /*<<< orphan*/  sport; int /*<<< orphan*/  lnk; } ;

/* Variables and functions */
 int AliasHandleUdpNbtNS (struct libalias*,struct ip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
protohandler2out(struct libalias *la, struct ip *pip, struct alias_data *ah)
{
	
	return (AliasHandleUdpNbtNS(la, pip, ah->lnk, &pip->ip_src, ah->sport,
 	    ah->aaddr, ah->aport));
}