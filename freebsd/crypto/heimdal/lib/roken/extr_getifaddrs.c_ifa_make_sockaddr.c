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
typedef  int /*<<< orphan*/  uint32_t ;
struct sockaddr_ll {size_t sll_halen; int /*<<< orphan*/  sll_addr; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int sa_family; int /*<<< orphan*/  sa_len; int /*<<< orphan*/  sa_data; } ;
typedef  int sa_family_t ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_PACKET 128 
 int /*<<< orphan*/  IN6_IS_ADDR_LINKLOCAL (void*) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_MC_LINKLOCAL (void*) ; 
 int /*<<< orphan*/  ifa_sa_len (int,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static void
ifa_make_sockaddr(sa_family_t family,
		  struct sockaddr *sa,
		  void *p, size_t len,
		  uint32_t scope, uint32_t scopeid)
{
  if (sa == NULL) return;
  switch(family){
  case AF_INET:
    memcpy(&((struct sockaddr_in*)sa)->sin_addr, (char *)p, len);
    break;
  case AF_INET6:
    memcpy(&((struct sockaddr_in6*)sa)->sin6_addr, (char *)p, len);
    if (IN6_IS_ADDR_LINKLOCAL(p) ||
	IN6_IS_ADDR_MC_LINKLOCAL(p)){
      ((struct sockaddr_in6*)sa)->sin6_scope_id = scopeid;
    }
    break;
  case AF_PACKET:
    memcpy(((struct sockaddr_ll*)sa)->sll_addr, (char *)p, len);
    ((struct sockaddr_ll*)sa)->sll_halen = len;
    break;
  default:
    memcpy(sa->sa_data, p, len);	/*XXX*/
    break;
  }
  sa->sa_family = family;
#ifdef HAVE_SOCKADDR_SA_LEN
  sa->sa_len = ifa_sa_len(family, len);
#endif
}