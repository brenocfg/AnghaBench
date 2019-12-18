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
struct mdoc_arg {struct mdoc_arg* argv; scalar_t__ argc; scalar_t__ refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  argn_free (struct mdoc_arg*,int) ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  free (struct mdoc_arg*) ; 

void
mdoc_argv_free(struct mdoc_arg *p)
{
	int		 i;

	if (NULL == p)
		return;

	if (p->refcnt) {
		--(p->refcnt);
		if (p->refcnt)
			return;
	}
	assert(p->argc);

	for (i = (int)p->argc - 1; i >= 0; i--)
		argn_free(p, i);

	free(p->argv);
	free(p);
}