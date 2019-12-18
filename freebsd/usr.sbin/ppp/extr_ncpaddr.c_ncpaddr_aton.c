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
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct ncprange {int ncprange_family; int ncprange_ip4width; int ncprange_ip6width; int /*<<< orphan*/  ncprange_ip6addr; TYPE_1__ ncprange_ip4addr; } ;
struct ncpaddr {int ncpaddr_family; int /*<<< orphan*/  ncpaddr_ip6addr; TYPE_1__ ncpaddr_ip4addr; } ;
struct ncp {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 scalar_t__ INADDR_ANY ; 
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  ncprange_aton (struct ncprange*,struct ncp*,char const*) ; 

int
ncpaddr_aton(struct ncpaddr *addr, struct ncp *ncp, const char *data)
{
  struct ncprange range;

  if (!ncprange_aton(&range, ncp, data))
    return 0;

  if (range.ncprange_family == AF_INET && range.ncprange_ip4width != 32 &&
      range.ncprange_ip4addr.s_addr != INADDR_ANY) {
    log_Printf(LogWARN, "ncpaddr_aton: %s: Only 32 bits allowed\n", data);
    return 0;
  }

#ifndef NOINET6
  if (range.ncprange_family == AF_INET6 && range.ncprange_ip6width != 128 &&
      !IN6_IS_ADDR_UNSPECIFIED(&range.ncprange_ip6addr)) {
    log_Printf(LogWARN, "ncpaddr_aton: %s: Only 128 bits allowed\n", data);
    return 0;
  }
#endif

  switch (range.ncprange_family) {
  case AF_INET:
    addr->ncpaddr_family = range.ncprange_family;
    addr->ncpaddr_ip4addr = range.ncprange_ip4addr;
    return 1;

#ifndef NOINET6
  case AF_INET6:
    addr->ncpaddr_family = range.ncprange_family;
    addr->ncpaddr_ip6addr = range.ncprange_ip6addr;
    return 1;
#endif
  }

  return 0;
}