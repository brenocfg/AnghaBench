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
struct TYPE_3__ {int /*<<< orphan*/  num_lids; int /*<<< orphan*/  lids; } ;
typedef  TYPE_1__ vltable_t ;
typedef  int /*<<< orphan*/  ib_net16_t ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_lids ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void vltable_sort_lids(vltable_t * vltable)
{
	qsort(vltable->lids, vltable->num_lids, sizeof(ib_net16_t), cmp_lids);
}