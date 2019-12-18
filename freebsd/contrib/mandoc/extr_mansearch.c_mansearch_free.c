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
struct manpage {struct manpage* output; struct manpage* names; struct manpage* file; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct manpage*) ; 

void
mansearch_free(struct manpage *res, size_t sz)
{
	size_t	 i;

	for (i = 0; i < sz; i++) {
		free(res[i].file);
		free(res[i].names);
		free(res[i].output);
	}
	free(res);
}