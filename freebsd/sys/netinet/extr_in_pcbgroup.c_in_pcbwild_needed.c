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
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct inpcb {int inp_flags2; int inp_vflag; TYPE_1__ inp_faddr; int /*<<< orphan*/  in6p_faddr; } ;

/* Variables and functions */
 int IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int INP_IPV6 ; 
 int INP_RSS_BUCKET_SET ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline int
in_pcbwild_needed(struct inpcb *inp)
{
#ifdef	RSS
	/*
	 * If it's a listen socket and INP_RSS_BUCKET_SET is set,
	 * it's a wildcard socket _but_ it's in a specific pcbgroup.
	 * Thus we don't treat it as a pcbwild inp.
	 */
	if (inp->inp_flags2 & INP_RSS_BUCKET_SET)
		return (0);
#endif

#ifdef INET6
	if (inp->inp_vflag & INP_IPV6)
		return (IN6_IS_ADDR_UNSPECIFIED(&inp->in6p_faddr));
	else
#endif
		return (inp->inp_faddr.s_addr == htonl(INADDR_ANY));
}