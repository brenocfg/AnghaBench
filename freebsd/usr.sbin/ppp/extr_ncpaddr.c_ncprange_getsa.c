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
struct sockaddr_storage {void* ss_family; } ;
struct sockaddr_in6 {int sin6_family; int sin6_len; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int sin_family; int sin_len; int /*<<< orphan*/  sin_addr; } ;
struct ncprange {int ncprange_family; int /*<<< orphan*/  ncprange_ip6width; int /*<<< orphan*/  ncprange_ip6addr; int /*<<< orphan*/  ncprange_ip4mask; int /*<<< orphan*/  ncprange_ip4addr; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 void* AF_UNSPEC ; 
 int /*<<< orphan*/  bits2mask6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,char,int) ; 

void
ncprange_getsa(const struct ncprange *range, struct sockaddr_storage *host,
               struct sockaddr_storage *mask)
{
  struct sockaddr_in *host4 = (struct sockaddr_in *)host;
  struct sockaddr_in *mask4 = (struct sockaddr_in *)mask;
#ifndef NOINET6
  struct sockaddr_in6 *host6 = (struct sockaddr_in6 *)host;
  struct sockaddr_in6 *mask6 = (struct sockaddr_in6 *)mask;
#endif

  memset(host, '\0', sizeof(*host));
  if (mask)
    memset(mask, '\0', sizeof(*mask));

  switch (range->ncprange_family) {
  case AF_INET:
    host4->sin_family = AF_INET;
    host4->sin_len = sizeof(*host4);
    host4->sin_addr = range->ncprange_ip4addr;
    if (mask4) {
      mask4->sin_family = AF_INET;
      mask4->sin_len = sizeof(*host4);
      mask4->sin_addr = range->ncprange_ip4mask;
    }
    break;

#ifndef NOINET6
  case AF_INET6:
    host6->sin6_family = AF_INET6;
    host6->sin6_len = sizeof(*host6);
    host6->sin6_addr = range->ncprange_ip6addr;
    if (mask6) {
      mask6->sin6_family = AF_INET6;
      mask6->sin6_len = sizeof(*host6);
      mask6->sin6_addr = bits2mask6(range->ncprange_ip6width);
    }
    break;
#endif

  default:
    host->ss_family = AF_UNSPEC;
    if (mask)
      mask->ss_family = AF_UNSPEC;
    break;
  }
}