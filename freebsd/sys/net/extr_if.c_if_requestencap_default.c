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
struct ifnet {int dummy; } ;
struct if_encap_req {scalar_t__ rtype; scalar_t__ bufsize; scalar_t__ lladdr_len; int family; scalar_t__ lladdr_off; int /*<<< orphan*/  lladdr; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EAFNOSUPPORT ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 scalar_t__ IFENCAP_LL ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
if_requestencap_default(struct ifnet *ifp, struct if_encap_req *req)
{

	if (req->rtype != IFENCAP_LL)
		return (EOPNOTSUPP);

	if (req->bufsize < req->lladdr_len)
		return (ENOMEM);

	switch (req->family) {
	case AF_INET:
	case AF_INET6:
		break;
	default:
		return (EAFNOSUPPORT);
	}

	/* Copy lladdr to storage as is */
	memmove(req->buf, req->lladdr, req->lladdr_len);
	req->bufsize = req->lladdr_len;
	req->lladdr_off = 0;

	return (0);
}