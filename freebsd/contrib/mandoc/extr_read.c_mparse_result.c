#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct roff_meta {scalar_t__ macroset; } ;
struct mparse {int options; TYPE_1__* man; } ;
struct TYPE_4__ {struct roff_meta meta; } ;

/* Variables and functions */
 scalar_t__ MACROSET_MDOC ; 
 int MPARSE_VALIDATE ; 
 int /*<<< orphan*/  man_validate (TYPE_1__*) ; 
 int /*<<< orphan*/  mdoc_validate (TYPE_1__*) ; 
 int /*<<< orphan*/  roff_state_reset (TYPE_1__*) ; 

struct roff_meta *
mparse_result(struct mparse *curp)
{
	roff_state_reset(curp->man);
	if (curp->options & MPARSE_VALIDATE) {
		if (curp->man->meta.macroset == MACROSET_MDOC)
			mdoc_validate(curp->man);
		else
			man_validate(curp->man);
	}
	return &curp->man->meta;
}