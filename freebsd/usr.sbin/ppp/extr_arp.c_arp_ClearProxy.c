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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct bundle {int dummy; } ;
struct arpreq {int /*<<< orphan*/  arp_pa; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ ID0ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  SET_SA_FAMILY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIOCDARP ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct arpreq*,char,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int
arp_ClearProxy(struct bundle *bundle, struct in_addr addr, int s)
{
  struct arpreq arpreq;

  memset(&arpreq, '\0', sizeof arpreq);
  SET_SA_FAMILY(arpreq.arp_pa, AF_INET);
  ((struct sockaddr_in *)&arpreq.arp_pa)->sin_addr.s_addr = addr.s_addr;
  if (ID0ioctl(s, SIOCDARP, (caddr_t) & arpreq) < 0) {
    log_Printf(LogERROR, "arp_ClearProxy: ioctl(SIOCDARP): %s\n",
               strerror(errno));
    return 0;
  }
  return 1;
}