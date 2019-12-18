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
struct resource {TYPE_1__* __r_i; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
struct TYPE_2__ {int /*<<< orphan*/  r_end; } ;

/* Variables and functions */

void
rman_set_end(struct resource *r, rman_res_t end)
{

	r->__r_i->r_end = end;
}