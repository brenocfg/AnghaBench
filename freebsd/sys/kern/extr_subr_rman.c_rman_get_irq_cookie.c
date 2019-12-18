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
struct TYPE_2__ {void* r_irq_cookie; } ;

/* Variables and functions */

void *
rman_get_irq_cookie(struct resource *r)
{

	return (r->__r_i->r_irq_cookie);
}