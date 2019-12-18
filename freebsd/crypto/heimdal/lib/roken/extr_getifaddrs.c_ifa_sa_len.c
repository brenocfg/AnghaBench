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
struct sockaddr_ll {int /*<<< orphan*/  sll_addr; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
typedef  int sa_family_t ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_PACKET 128 

__attribute__((used)) static size_t
ifa_sa_len(sa_family_t family, int len)
{
  size_t size;
  switch(family){
  case AF_INET:
    size = sizeof(struct sockaddr_in);
    break;
  case AF_INET6:
    size = sizeof(struct sockaddr_in6);
    break;
  case AF_PACKET:
    size = (size_t)(((struct sockaddr_ll *)NULL)->sll_addr) + len;
    if (size < sizeof(struct sockaddr_ll))
      size = sizeof(struct sockaddr_ll);
    break;
  default:
    size = (size_t)(((struct sockaddr *)NULL)->sa_data) + len;
    if (size < sizeof(struct sockaddr))
      size = sizeof(struct sockaddr);
    break;
  }
  return size;
}