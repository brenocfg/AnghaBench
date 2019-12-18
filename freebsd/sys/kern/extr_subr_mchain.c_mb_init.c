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
struct mbuf {scalar_t__ m_len; } ;
struct mbchain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct mbuf* m_gethdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_initm (struct mbchain*,struct mbuf*) ; 

int
mb_init(struct mbchain *mbp)
{
	struct mbuf *m;

	m = m_gethdr(M_WAITOK, MT_DATA);
	m->m_len = 0;
	mb_initm(mbp, m);
	return (0);
}