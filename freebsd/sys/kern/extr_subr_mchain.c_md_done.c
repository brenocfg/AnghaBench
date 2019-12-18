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
struct mdchain {int /*<<< orphan*/ * md_top; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

void
md_done(struct mdchain *mdp)
{
	if (mdp->md_top) {
		m_freem(mdp->md_top);
		mdp->md_top = NULL;
	}
}