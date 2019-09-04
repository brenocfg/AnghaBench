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
struct ifaddrs {int ifa_flags; TYPE_1__* ifa_addr; } ;
struct TYPE_2__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_LINK ; 
 int IFF_RUNNING ; 
 int IFF_UP ; 
 int UV__EXCLUDE_IFPHYS ; 

__attribute__((used)) static int uv__ifaddr_exclude(struct ifaddrs *ent, int exclude_type) {
  if (!((ent->ifa_flags & IFF_UP) && (ent->ifa_flags & IFF_RUNNING)))
    return 1;
  if (ent->ifa_addr == NULL)
    return 1;
#if !defined(__CYGWIN__) && !defined(__MSYS__)
  /*
   * If `exclude_type` is `UV__EXCLUDE_IFPHYS`, just see whether `sa_family`
   * equals to `AF_LINK` or not. Otherwise, the result depends on the operation
   * system with `AF_LINK` or `PF_INET`.
   */
  if (exclude_type == UV__EXCLUDE_IFPHYS)
    return (ent->ifa_addr->sa_family != AF_LINK);
#endif
#if defined(__APPLE__) || defined(__FreeBSD__) || defined(__DragonFly__)
  /*
   * On BSD getifaddrs returns information related to the raw underlying
   * devices.  We're not interested in this information.
   */
  if (ent->ifa_addr->sa_family == AF_LINK)
    return 1;
#elif defined(__NetBSD__) || defined(__OpenBSD__)
  if (ent->ifa_addr->sa_family != PF_INET &&
      ent->ifa_addr->sa_family != PF_INET6)
    return 1;
#endif
  return 0;
}