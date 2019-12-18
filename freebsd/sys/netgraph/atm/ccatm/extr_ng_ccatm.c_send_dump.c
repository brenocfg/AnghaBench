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
struct TYPE_2__ {scalar_t__ len; } ;
struct mbuf {scalar_t__ m_len; TYPE_1__ m_pkthdr; int /*<<< orphan*/  m_data; struct mbuf* m_next; } ;
struct ccnode {struct mbuf* dump_first; struct mbuf* dump_last; int /*<<< orphan*/ * dump; } ;
struct ccdata {int dummy; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_getcl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int
send_dump(struct ccdata *data, void *uarg, const char *buf)
{
	struct mbuf *m;
	struct ccnode *priv = uarg;

	if (priv->dump == NULL) {
		m = m_getcl(M_NOWAIT, MT_DATA, M_PKTHDR);
		if (m == NULL)
			return (ENOBUFS);
		priv->dump_first = priv->dump_last = m;
		m->m_pkthdr.len = 0;
	} else {
		m = m_getcl(M_NOWAIT, MT_DATA, 0);
		if (m == NULL) {
			m_freem(priv->dump_first);
			return (ENOBUFS);
		}
		priv->dump_last->m_next = m;
		priv->dump_last = m;
	}

	strcpy(m->m_data, buf);
	priv->dump_first->m_pkthdr.len += (m->m_len = strlen(buf));

	return (0);
}