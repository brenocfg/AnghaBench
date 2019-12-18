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
struct TYPE_2__ {int len; } ;
struct mbuf {int m_len; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int MCLBYTES ; 
 int /*<<< orphan*/  MC_RAW_WR ; 
 int MHLEN ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int /*<<< orphan*/  howmany (int,int) ; 
 struct mbuf* m_getcl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mbuf* m_gethdr (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mbuf_cflags (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mbuf_len16 (struct mbuf*,int /*<<< orphan*/ ) ; 

struct mbuf *
alloc_wr_mbuf(int len, int how)
{
	struct mbuf *m;

	if (len <= MHLEN)
		m = m_gethdr(how, MT_DATA);
	else if (len <= MCLBYTES)
		m = m_getcl(how, MT_DATA, M_PKTHDR);
	else
		m = NULL;
	if (m == NULL)
		return (NULL);
	m->m_pkthdr.len = len;
	m->m_len = len;
	set_mbuf_cflags(m, MC_RAW_WR);
	set_mbuf_len16(m, howmany(len, 16));
	return (m);
}