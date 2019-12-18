#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void* netmask4; void* netmask6; } ;
struct TYPE_8__ {void* address4; void* address6; } ;
struct TYPE_12__ {char* name; int is_internal; int /*<<< orphan*/  phys_addr; TYPE_2__ netmask; TYPE_1__ address; } ;
typedef  TYPE_5__ uv_interface_address_t ;
struct sockaddr_ll {int /*<<< orphan*/  sll_addr; } ;
typedef  void* sockaddr_in6 ;
typedef  void* sockaddr_in ;
struct ifaddrs {int ifa_flags; TYPE_4__* ifa_addr; int /*<<< orphan*/  ifa_name; struct ifaddrs* ifa_next; TYPE_3__* ifa_netmask; } ;
struct TYPE_11__ {scalar_t__ sa_family; } ;
struct TYPE_10__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int IFF_LOOPBACK ; 
 int UV_ENOMEM ; 
 int UV_ENOSYS ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UV__EXCLUDE_IFADDR ; 
 int /*<<< orphan*/  UV__EXCLUDE_IFPHYS ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 scalar_t__ getifaddrs (struct ifaddrs**) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,size_t) ; 
 TYPE_5__* uv__calloc (int,int) ; 
 scalar_t__ uv__ifaddr_exclude (struct ifaddrs*,int /*<<< orphan*/ ) ; 
 char* uv__strdup (int /*<<< orphan*/ ) ; 

int uv_interface_addresses(uv_interface_address_t** addresses, int* count) {
#ifndef HAVE_IFADDRS_H
  *count = 0;
  *addresses = NULL;
  return UV_ENOSYS;
#else
  struct ifaddrs *addrs, *ent;
  uv_interface_address_t* address;
  int i;
  struct sockaddr_ll *sll;

  *count = 0;
  *addresses = NULL;

  if (getifaddrs(&addrs))
    return UV__ERR(errno);

  /* Count the number of interfaces */
  for (ent = addrs; ent != NULL; ent = ent->ifa_next) {
    if (uv__ifaddr_exclude(ent, UV__EXCLUDE_IFADDR))
      continue;

    (*count)++;
  }

  if (*count == 0) {
    freeifaddrs(addrs);
    return 0;
  }

  /* Make sure the memory is initiallized to zero using calloc() */
  *addresses = uv__calloc(*count, sizeof(**addresses));
  if (!(*addresses)) {
    freeifaddrs(addrs);
    return UV_ENOMEM;
  }

  address = *addresses;

  for (ent = addrs; ent != NULL; ent = ent->ifa_next) {
    if (uv__ifaddr_exclude(ent, UV__EXCLUDE_IFADDR))
      continue;

    address->name = uv__strdup(ent->ifa_name);

    if (ent->ifa_addr->sa_family == AF_INET6) {
      address->address.address6 = *((struct sockaddr_in6*) ent->ifa_addr);
    } else {
      address->address.address4 = *((struct sockaddr_in*) ent->ifa_addr);
    }

    if (ent->ifa_netmask->sa_family == AF_INET6) {
      address->netmask.netmask6 = *((struct sockaddr_in6*) ent->ifa_netmask);
    } else {
      address->netmask.netmask4 = *((struct sockaddr_in*) ent->ifa_netmask);
    }

    address->is_internal = !!(ent->ifa_flags & IFF_LOOPBACK);

    address++;
  }

  /* Fill in physical addresses for each interface */
  for (ent = addrs; ent != NULL; ent = ent->ifa_next) {
    if (uv__ifaddr_exclude(ent, UV__EXCLUDE_IFPHYS))
      continue;

    address = *addresses;

    for (i = 0; i < (*count); i++) {
      size_t namelen = strlen(ent->ifa_name);
      /* Alias interface share the same physical address */
      if (strncmp(address->name, ent->ifa_name, namelen) == 0 &&
          (address->name[namelen] == 0 || address->name[namelen] == ':')) {
        sll = (struct sockaddr_ll*)ent->ifa_addr;
        memcpy(address->phys_addr, sll->sll_addr, sizeof(address->phys_addr));
      }
      address++;
    }
  }

  freeifaddrs(addrs);

  return 0;
#endif
}