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
struct mparse {scalar_t__ gzip; int /*<<< orphan*/ * secondary; int /*<<< orphan*/  man; int /*<<< orphan*/  roff; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_buf_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  roff_man_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roff_reset (int /*<<< orphan*/ ) ; 

void
mparse_reset(struct mparse *curp)
{
	roff_reset(curp->roff);
	roff_man_reset(curp->man);
	free_buf_list(curp->secondary);
	curp->secondary = NULL;
	curp->gzip = 0;
}