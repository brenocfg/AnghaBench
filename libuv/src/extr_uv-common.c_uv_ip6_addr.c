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
struct sockaddr_in6 {int sin6_len; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; } ;
typedef  int /*<<< orphan*/  address_part ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  atoi (char const*) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  if_nametoindex (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 char* strchr (char const*,char) ; 
 int uv_inet_pton (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

int uv_ip6_addr(const char* ip, int port, struct sockaddr_in6* addr) {
  char address_part[40];
  size_t address_part_size;
  const char* zone_index;

  memset(addr, 0, sizeof(*addr));
  addr->sin6_family = AF_INET6;
  addr->sin6_port = htons(port);
#ifdef SIN6_LEN
  addr->sin6_len = sizeof(*addr);
#endif

  zone_index = strchr(ip, '%');
  if (zone_index != NULL) {
    address_part_size = zone_index - ip;
    if (address_part_size >= sizeof(address_part))
      address_part_size = sizeof(address_part) - 1;

    memcpy(address_part, ip, address_part_size);
    address_part[address_part_size] = '\0';
    ip = address_part;

    zone_index++; /* skip '%' */
    /* NOTE: unknown interface (id=0) is silently ignored */
#ifdef _WIN32
    addr->sin6_scope_id = atoi(zone_index);
#else
    addr->sin6_scope_id = if_nametoindex(zone_index);
#endif
  }

  return uv_inet_pton(AF_INET6, ip, &addr->sin6_addr);
}