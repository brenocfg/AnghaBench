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
struct mparse {int /*<<< orphan*/  secondary; int /*<<< orphan*/  roff; TYPE_1__* man; } ;
struct TYPE_2__ {int /*<<< orphan*/  manmac; int /*<<< orphan*/  mdocmac; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct mparse*) ; 
 int /*<<< orphan*/  free_buf_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roff_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roff_man_free (TYPE_1__*) ; 
 int /*<<< orphan*/  roffhash_free (int /*<<< orphan*/ ) ; 

void
mparse_free(struct mparse *curp)
{
	roffhash_free(curp->man->mdocmac);
	roffhash_free(curp->man->manmac);
	roff_man_free(curp->man);
	roff_free(curp->roff);
	free_buf_list(curp->secondary);
	free(curp);
}