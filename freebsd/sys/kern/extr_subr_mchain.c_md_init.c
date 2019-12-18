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
struct mdchain {int dummy; } ;
struct mbuf {scalar_t__ m_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct mbuf* m_gethdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_initm (struct mdchain*,struct mbuf*) ; 

int
md_init(struct mdchain *mdp)
{
	struct mbuf *m;

	m = m_gethdr(M_WAITOK, MT_DATA);
	m->m_len = 0;
	md_initm(mdp, m);
	return (0);
}