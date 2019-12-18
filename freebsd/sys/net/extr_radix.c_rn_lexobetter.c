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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int LEN (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int	/* XXX: arbitrary ordering for non-contiguous masks */
rn_lexobetter(void *m_arg, void *n_arg)
{
	u_char *mp = m_arg, *np = n_arg, *lim;

	if (LEN(mp) > LEN(np))
		return (1);  /* not really, but need to check longer one first */
	if (LEN(mp) == LEN(np))
		for (lim = mp + LEN(mp); mp < lim;)
			if (*mp++ > *np++)
				return (1);
	return (0);
}