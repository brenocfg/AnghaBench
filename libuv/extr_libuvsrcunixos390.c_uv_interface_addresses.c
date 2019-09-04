#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in {int dummy; } ;
struct sockaddr_in6 {int dummy; } ;
struct TYPE_11__ {struct sockaddr_in address4; struct sockaddr_in6 address6; } ;
struct TYPE_13__ {int is_internal; int /*<<< orphan*/  phys_addr; TYPE_1__ address; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ uv_interface_address_t ;
struct TYPE_12__ {int sa_len; scalar_t__ sa_family; } ;
struct ifreq {int ifc_len; int ifr_flags; TYPE_2__ ifr_addr; TYPE_3__* ifr_name; struct ifreq* ifc_req; } ;
struct ifconf {int ifc_len; int ifr_flags; TYPE_2__ ifr_addr; TYPE_3__* ifr_name; struct ifconf* ifc_req; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int IFF_LOOPBACK ; 
 int IFF_RUNNING ; 
 int IFF_UP ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  SIOCGIFCONF ; 
 int /*<<< orphan*/  SIOCGIFFLAGS ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int UV_ENOMEM ; 
 int UV_ENOSYS ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int socket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ifreq* uv__calloc (int,int) ; 
 int /*<<< orphan*/  uv__close (int) ; 
 int /*<<< orphan*/  uv__free (TYPE_3__*) ; 
 int /*<<< orphan*/  uv__interface_addresses_v6 (TYPE_3__**,int*) ; 
 TYPE_3__* uv__malloc (int) ; 
 int /*<<< orphan*/  uv__strdup (TYPE_3__*) ; 

int uv_interface_addresses(uv_interface_address_t** addresses, int* count) {
  uv_interface_address_t* address;
  int sockfd;
  int maxsize;
  struct ifconf ifc;
  struct ifreq flg;
  struct ifreq* ifr;
  struct ifreq* p;
  int count_v6;

  *count = 0;
  *addresses = NULL;

  /* get the ipv6 addresses first */
  uv_interface_address_t* addresses_v6;
  uv__interface_addresses_v6(&addresses_v6, &count_v6);

  /* now get the ipv4 addresses */

  /* Assume maximum buffer size allowable */
  maxsize = 16384;

  sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
  if (0 > sockfd)
    return UV__ERR(errno);

  ifc.ifc_req = uv__calloc(1, maxsize);
  ifc.ifc_len = maxsize;
  if (ioctl(sockfd, SIOCGIFCONF, &ifc) == -1) {
    uv__close(sockfd);
    return UV__ERR(errno);
  }

#define MAX(a,b) (((a)>(b))?(a):(b))
#define ADDR_SIZE(p) MAX((p).sa_len, sizeof(p))

  /* Count all up and running ipv4/ipv6 addresses */
  ifr = ifc.ifc_req;
  while ((char*)ifr < (char*)ifc.ifc_req + ifc.ifc_len) {
    p = ifr;
    ifr = (struct ifreq*)
      ((char*)ifr + sizeof(ifr->ifr_name) + ADDR_SIZE(ifr->ifr_addr));

    if (!(p->ifr_addr.sa_family == AF_INET6 ||
          p->ifr_addr.sa_family == AF_INET))
      continue;

    memcpy(flg.ifr_name, p->ifr_name, sizeof(flg.ifr_name));
    if (ioctl(sockfd, SIOCGIFFLAGS, &flg) == -1) {
      uv__close(sockfd);
      return UV__ERR(errno);
    }

    if (!(flg.ifr_flags & IFF_UP && flg.ifr_flags & IFF_RUNNING))
      continue;

    (*count)++;
  }

  if (*count == 0) {
    uv__close(sockfd);
    return 0;
  }

  /* Alloc the return interface structs */
  *addresses = uv__malloc((*count + count_v6) *
                          sizeof(uv_interface_address_t));

  if (!(*addresses)) {
    uv__close(sockfd);
    return UV_ENOMEM;
  }
  address = *addresses;

  /* copy over the ipv6 addresses */
  memcpy(address, addresses_v6, count_v6 * sizeof(uv_interface_address_t));
  address += count_v6;
  *count += count_v6;
  uv__free(addresses_v6);

  ifr = ifc.ifc_req;
  while ((char*)ifr < (char*)ifc.ifc_req + ifc.ifc_len) {
    p = ifr;
    ifr = (struct ifreq*)
      ((char*)ifr + sizeof(ifr->ifr_name) + ADDR_SIZE(ifr->ifr_addr));

    if (!(p->ifr_addr.sa_family == AF_INET6 ||
          p->ifr_addr.sa_family == AF_INET))
      continue;

    memcpy(flg.ifr_name, p->ifr_name, sizeof(flg.ifr_name));
    if (ioctl(sockfd, SIOCGIFFLAGS, &flg) == -1) {
      uv__close(sockfd);
      return UV_ENOSYS;
    }

    if (!(flg.ifr_flags & IFF_UP && flg.ifr_flags & IFF_RUNNING))
      continue;

    /* All conditions above must match count loop */

    address->name = uv__strdup(p->ifr_name);

    if (p->ifr_addr.sa_family == AF_INET6) {
      address->address.address6 = *((struct sockaddr_in6*) &p->ifr_addr);
    } else {
      address->address.address4 = *((struct sockaddr_in*) &p->ifr_addr);
    }

    address->is_internal = flg.ifr_flags & IFF_LOOPBACK ? 1 : 0;
    memset(address->phys_addr, 0, sizeof(address->phys_addr));
    address++;
  }

#undef ADDR_SIZE
#undef MAX

  uv__close(sockfd);
  return 0;
}