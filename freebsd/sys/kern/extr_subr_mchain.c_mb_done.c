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
struct mbchain {int /*<<< orphan*/ * mb_top; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

void
mb_done(struct mbchain *mbp)
{
	if (mbp->mb_top) {
		m_freem(mbp->mb_top);
		mbp->mb_top = NULL;
	}
}