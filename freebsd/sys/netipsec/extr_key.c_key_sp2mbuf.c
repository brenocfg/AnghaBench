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
struct secpolicy {int dummy; } ;
struct mbuf {size_t m_len; int /*<<< orphan*/  m_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 size_t key_getspreqmsglen (struct secpolicy*) ; 
 scalar_t__ key_sp2msg (struct secpolicy*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  m_align (struct mbuf*,size_t) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_get2 (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mbuf *
key_sp2mbuf(struct secpolicy *sp)
{
	struct mbuf *m;
	size_t tlen;

	tlen = key_getspreqmsglen(sp);
	m = m_get2(tlen, M_NOWAIT, MT_DATA, 0);
	if (m == NULL)
		return (NULL);
	m_align(m, tlen);
	m->m_len = tlen;
	if (key_sp2msg(sp, m->m_data, &tlen) != 0) {
		m_freem(m);
		return (NULL);
	}
	return (m);
}