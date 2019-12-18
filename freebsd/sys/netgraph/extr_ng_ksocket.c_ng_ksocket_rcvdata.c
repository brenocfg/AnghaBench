#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct socket {int dummy; } ;
struct sockaddr {int dummy; } ;
struct sa_tag {scalar_t__ id; struct sockaddr sa; } ;
struct mbuf {int m_flags; } ;
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_3__ {struct socket* so; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGNED_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOBUFS ; 
 int M_BCAST ; 
 int M_MCAST ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGI_GET_M (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  NGM_KSOCKET_COOKIE ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_KSOCKET_TAG_SOCKADDR ; 
 scalar_t__ NG_NODE_ID (int /*<<< orphan*/  const) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  caddr_t ; 
 struct thread* curthread ; 
 struct mbuf* m_defrag (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 scalar_t__ m_tag_locate (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtod (struct mbuf*,int /*<<< orphan*/ ) ; 
 int sosend (struct socket* const,struct sockaddr*,int /*<<< orphan*/ ,struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  uint32_t ; 

__attribute__((used)) static int
ng_ksocket_rcvdata(hook_p hook, item_p item)
{
	struct thread *td = curthread;	/* XXX broken */
	const node_p node = NG_HOOK_NODE(hook);
	const priv_p priv = NG_NODE_PRIVATE(node);
	struct socket *const so = priv->so;
	struct sockaddr *sa = NULL;
	int error;
	struct mbuf *m;
#ifdef ALIGNED_POINTER
	struct mbuf *n;
#endif /* ALIGNED_POINTER */
	struct sa_tag *stag;

	/* Extract data */
	NGI_GET_M(item, m);
	NG_FREE_ITEM(item);
#ifdef ALIGNED_POINTER
	if (!ALIGNED_POINTER(mtod(m, caddr_t), uint32_t)) {
		n = m_defrag(m, M_NOWAIT);
		if (n == NULL) {
			m_freem(m);
			return (ENOBUFS);
		}
		m = n;
	}
#endif /* ALIGNED_POINTER */
	/*
	 * Look if socket address is stored in packet tags.
	 * If sockaddr is ours, or provided by a third party (zero id),
	 * then we accept it.
	 */
	if (((stag = (struct sa_tag *)m_tag_locate(m, NGM_KSOCKET_COOKIE,
	    NG_KSOCKET_TAG_SOCKADDR, NULL)) != NULL) &&
	    (stag->id == NG_NODE_ID(node) || stag->id == 0))
		sa = &stag->sa;

	/* Reset specific mbuf flags to prevent addressing problems. */
	m->m_flags &= ~(M_BCAST|M_MCAST);

	/* Send packet */
	error = sosend(so, sa, 0, m, 0, 0, td);

	return (error);
}