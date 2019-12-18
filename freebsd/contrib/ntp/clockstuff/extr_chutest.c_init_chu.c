#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  l_uf; scalar_t__ l_ui; } ;
struct TYPE_6__ {int /*<<< orphan*/  l_uf; scalar_t__ l_ui; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFFILTFUDGE ; 
 int /*<<< orphan*/  DEFPROPDELAY ; 
 int /*<<< orphan*/  L_ADD (TYPE_1__*,TYPE_3__*) ; 
 TYPE_3__ fudgefactor ; 
 TYPE_1__ offset_fudge ; 
 TYPE_1__ propagation_delay ; 
 scalar_t__ yearstart ; 

void
init_chu(void)
{

	/*
	 * Initialize fudge factors to default.
	 */
	propagation_delay.l_ui = 0;
	propagation_delay.l_uf = DEFPROPDELAY;
	fudgefactor.l_ui = 0;
	fudgefactor.l_uf = DEFFILTFUDGE;
	offset_fudge = propagation_delay;
	L_ADD(&offset_fudge, &fudgefactor);

	yearstart = 0;
}