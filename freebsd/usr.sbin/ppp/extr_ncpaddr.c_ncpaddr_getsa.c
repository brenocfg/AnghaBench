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
struct sockaddr_storage {int /*<<< orphan*/  ss_family; } ;
struct sockaddr_in6 {int sin6_family; int sin6_len; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int sin_family; int sin_len; int /*<<< orphan*/  sin_addr; } ;
struct ncpaddr {int ncpaddr_family; int /*<<< orphan*/  ncpaddr_ip6addr; int /*<<< orphan*/  ncpaddr_ip4addr; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,char,int) ; 

void
ncpaddr_getsa(const struct ncpaddr *addr, struct sockaddr_storage *host)
{
  struct sockaddr_in *host4 = (struct sockaddr_in *)host;
#ifndef NOINET6
  struct sockaddr_in6 *host6 = (struct sockaddr_in6 *)host;
#endif

  memset(host, '\0', sizeof(*host));

  switch (addr->ncpaddr_family) {
  case AF_INET:
    host4->sin_family = AF_INET;
    host4->sin_len = sizeof(*host4);
    host4->sin_addr = addr->ncpaddr_ip4addr;
    break;

#ifndef NOINET6
  case AF_INET6:
    host6->sin6_family = AF_INET6;
    host6->sin6_len = sizeof(*host6);
    host6->sin6_addr = addr->ncpaddr_ip6addr;
    break;
#endif

  default:
    host->ss_family = AF_UNSPEC;
    break;
  }
}