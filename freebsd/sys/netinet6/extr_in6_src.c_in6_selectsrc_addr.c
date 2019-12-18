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
struct in6_addr {int dummy; } ;
struct sockaddr_in6 {int sin6_len; int /*<<< orphan*/  sin6_scope_id; struct in6_addr sin6_addr; int /*<<< orphan*/  sin6_family; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  dst_sa ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in6*,int) ; 
 int in6_selecthlim (int /*<<< orphan*/ *,struct ifnet*) ; 
 int in6_selectsrc (int /*<<< orphan*/ ,struct sockaddr_in6*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ifnet**,struct in6_addr*) ; 
 int /*<<< orphan*/  sa6_embedscope (struct sockaddr_in6*,int /*<<< orphan*/ ) ; 

int
in6_selectsrc_addr(uint32_t fibnum, const struct in6_addr *dst,
    uint32_t scopeid, struct ifnet *ifp, struct in6_addr *srcp,
    int *hlim)
{
	struct ifnet *retifp;
	struct sockaddr_in6 dst_sa;
	int error;

	retifp = ifp;
	bzero(&dst_sa, sizeof(dst_sa));
	dst_sa.sin6_family = AF_INET6;
	dst_sa.sin6_len = sizeof(dst_sa);
	dst_sa.sin6_addr = *dst;
	dst_sa.sin6_scope_id = scopeid;
	sa6_embedscope(&dst_sa, 0);

	error = in6_selectsrc(fibnum, &dst_sa, NULL, NULL, NULL, &retifp, srcp);
	if (hlim != NULL)
		*hlim = in6_selecthlim(NULL, retifp);

	return (error);
}