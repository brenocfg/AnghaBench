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
struct mdchain {TYPE_1__* md_top; } ;
struct mbuf {int dummy; } ;
struct TYPE_2__ {struct mbuf* m_nextpkt; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  md_done (struct mdchain*) ; 
 int /*<<< orphan*/  md_initm (struct mdchain*,struct mbuf*) ; 

int
md_next_record(struct mdchain *mdp)
{
	struct mbuf *m;

	if (mdp->md_top == NULL)
		return (ENOENT);
	m = mdp->md_top->m_nextpkt;
	md_done(mdp);
	if (m == NULL)
		return (ENOENT);
	md_initm(mdp, m);
	return (0);
}