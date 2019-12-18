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
struct TYPE_4__ {int num_lids; int /*<<< orphan*/ * vls; } ;
typedef  TYPE_1__ vltable_t ;
typedef  int int64_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  ib_net16_t ;

/* Variables and functions */
 int vltable_get_lidindex (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int32_t vltable_get_vl(vltable_t * vltable, ib_net16_t slid, ib_net16_t dlid)
{
	int64_t ind1 = vltable_get_lidindex(&slid, vltable);
	int64_t ind2 = vltable_get_lidindex(&dlid, vltable);

	if (ind1 > -1 && ind2 > -1)
		return (int32_t) (vltable->
				  vls[ind1 + ind2 * vltable->num_lids]);
	else
		return -1;
}