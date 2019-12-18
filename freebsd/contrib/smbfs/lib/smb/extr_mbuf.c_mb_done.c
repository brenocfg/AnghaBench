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
struct mbdata {int /*<<< orphan*/ * mb_top; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

int
mb_done(struct mbdata *mbp)
{
	if (mbp->mb_top) {
		m_freem(mbp->mb_top);
		mbp->mb_top = NULL;
	}
	return 0;
}