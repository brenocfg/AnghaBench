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
struct roff {int mstacksz; int /*<<< orphan*/  reqtab; struct roff* mstack; struct roff* argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct roff*) ; 
 int /*<<< orphan*/  roff_free1 (struct roff*) ; 
 int /*<<< orphan*/  roffhash_free (int /*<<< orphan*/ ) ; 

void
roff_free(struct roff *r)
{
	int		 i;

	roff_free1(r);
	for (i = 0; i < r->mstacksz; i++)
		free(r->mstack[i].argv);
	free(r->mstack);
	roffhash_free(r->reqtab);
	free(r);
}