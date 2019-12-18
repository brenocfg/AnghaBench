#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct re_guts {scalar_t__ magic; char* must; int /*<<< orphan*/ * setbits; int /*<<< orphan*/ * sets; int /*<<< orphan*/ * strip; } ;
struct TYPE_3__ {scalar_t__ re_magic; struct re_guts* re_g; } ;
typedef  TYPE_1__ llvm_regex_t ;

/* Variables and functions */
 scalar_t__ MAGIC1 ; 
 scalar_t__ MAGIC2 ; 
 int /*<<< orphan*/  free (char*) ; 

void
llvm_regfree(llvm_regex_t *preg)
{
	struct re_guts *g;

	if (preg->re_magic != MAGIC1)	/* oops */
		return;			/* nice to complain, but hard */

	g = preg->re_g;
	if (g == NULL || g->magic != MAGIC2)	/* oops again */
		return;
	preg->re_magic = 0;		/* mark it invalid */
	g->magic = 0;			/* mark it invalid */

	if (g->strip != NULL)
		free((char *)g->strip);
	if (g->sets != NULL)
		free((char *)g->sets);
	if (g->setbits != NULL)
		free((char *)g->setbits);
	if (g->must != NULL)
		free(g->must);
	free((char *)g);
}