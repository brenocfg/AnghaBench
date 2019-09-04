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
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int IFF_RUNNING ; 
 int IFF_UP ; 

__attribute__((used)) static int uv__ifaddr_exclude(struct ifaddrs *ent) {
  if (!((ent->ifa_flags & IFF_UP) && (ent->ifa_flags & IFF_RUNNING)))
    return 1;
  if (ent->ifa_addr == NULL)
    return 1;
  if (ent->ifa_addr->sa_family != AF_INET &&
      ent->ifa_addr->sa_family != AF_INET6)
    return 1;
  return 0;
}