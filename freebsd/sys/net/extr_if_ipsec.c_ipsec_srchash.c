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
typedef  size_t uint32_t ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {int sa_family; } ;
struct ipsec_iflist {int dummy; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  in_addr_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  FNV1_32_INIT ; 
 int /*<<< orphan*/  IPSEC_HASH_SIZE ; 
 struct ipsec_iflist* V_ipsec4_srchtbl ; 
 struct ipsec_iflist* V_ipsec6_srchtbl ; 
 size_t fnv_32_buf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ipsec_iflist *
ipsec_srchash(const struct sockaddr *sa)
{
	uint32_t hval;

	switch (sa->sa_family) {
#ifdef INET
	case AF_INET:
		hval = fnv_32_buf(
		    &((const struct sockaddr_in *)sa)->sin_addr.s_addr,
		    sizeof(in_addr_t), FNV1_32_INIT);
		return (&V_ipsec4_srchtbl[hval & (IPSEC_HASH_SIZE - 1)]);
#endif
#ifdef INET6
	case AF_INET6:
		hval = fnv_32_buf(
		    &((const struct sockaddr_in6 *)sa)->sin6_addr,
		    sizeof(struct in6_addr), FNV1_32_INIT);
		return (&V_ipsec6_srchtbl[hval & (IPSEC_HASH_SIZE - 1)]);
#endif
	}
	return (NULL);
}