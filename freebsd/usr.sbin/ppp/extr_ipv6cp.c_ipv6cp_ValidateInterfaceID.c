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
typedef  int /*<<< orphan*/ ** u_char ;
struct ipv6cp {int /*<<< orphan*/ **** his_ifid; int /*<<< orphan*/ **** my_ifid; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/  id; } ;
struct fsm_opt {int /*<<< orphan*/ *** data; TYPE_1__ hdr; } ;
struct fsm_decode {int dummy; } ;

/* Variables and functions */
 int IPV6CP_IFIDLEN ; 
 int /*<<< orphan*/  TY_TOKEN ; 
 int /*<<< orphan*/  fsm_ack (struct fsm_decode*,struct fsm_opt*) ; 
 int /*<<< orphan*/  fsm_nak (struct fsm_decode*,struct fsm_opt*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ***,int /*<<< orphan*/ ***,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ ***,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ***,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ipv6cp_ValidateInterfaceID(struct ipv6cp *ipv6cp, u_char *ifid,
			   struct fsm_decode *dec)
{
  struct fsm_opt opt;
  u_char zero[IPV6CP_IFIDLEN];

  memset(zero, 0, IPV6CP_IFIDLEN);

  if (memcmp(ifid, zero, IPV6CP_IFIDLEN) != 0
      && memcmp(ifid, ipv6cp->my_ifid, IPV6CP_IFIDLEN) != 0)
    memcpy(ipv6cp->his_ifid, ifid, IPV6CP_IFIDLEN);

  opt.hdr.id = TY_TOKEN;
  opt.hdr.len = IPV6CP_IFIDLEN + 2;
  memcpy(opt.data, &ipv6cp->his_ifid, IPV6CP_IFIDLEN);
  if (memcmp(ifid, ipv6cp->his_ifid, IPV6CP_IFIDLEN) == 0)
    fsm_ack(dec, &opt);
  else
    fsm_nak(dec, &opt);
}