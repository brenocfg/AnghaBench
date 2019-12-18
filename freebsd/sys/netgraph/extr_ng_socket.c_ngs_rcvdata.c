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
struct socket {int /*<<< orphan*/  so_rcv; } ;
struct sockaddr_ng {int sg_len; char* sg_data; int /*<<< orphan*/  sg_family; } ;
struct sockaddr {int dummy; } ;
struct ngsock {struct ngpcb* datasock; } ;
struct ngpcb {struct socket* ng_socket; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;

/* Variables and functions */
 int /*<<< orphan*/  AF_NETGRAPH ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  NGI_GET_M (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_FREE_M (struct mbuf*) ; 
 int /*<<< orphan*/  NG_HOOKSIZ ; 
 int /*<<< orphan*/  NG_HOOK_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 struct ngsock* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRAP_ERROR ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 scalar_t__ sbappendaddr (int /*<<< orphan*/ *,struct sockaddr*,struct mbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sorwakeup (struct socket*) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ngs_rcvdata(hook_p hook, item_p item)
{
	struct ngsock *const priv = NG_NODE_PRIVATE(NG_HOOK_NODE(hook));
	struct ngpcb *const pcbp = priv->datasock;
	struct socket *so;
	struct sockaddr_ng *addr;
	char *addrbuf[NG_HOOKSIZ + 4];
	int addrlen;
	struct mbuf *m;

	NGI_GET_M(item, m);
	NG_FREE_ITEM(item);

	/* If there is no data socket, black-hole it. */
	if (pcbp == NULL) {
		NG_FREE_M(m);
		return (0);
	}
	so = pcbp->ng_socket;

	/* Get the return address into a sockaddr. */
	addrlen = strlen(NG_HOOK_NAME(hook));	/* <= NG_HOOKSIZ - 1 */
	addr = (struct sockaddr_ng *) addrbuf;
	addr->sg_len = addrlen + 3;
	addr->sg_family = AF_NETGRAPH;
	bcopy(NG_HOOK_NAME(hook), addr->sg_data, addrlen);
	addr->sg_data[addrlen] = '\0';

	/* Try to tell the socket which hook it came in on. */
	if (sbappendaddr(&so->so_rcv, (struct sockaddr *)addr, m, NULL) == 0) {
		m_freem(m);
		TRAP_ERROR;
		return (ENOBUFS);
	}
	sorwakeup(so);
	return (0);
}