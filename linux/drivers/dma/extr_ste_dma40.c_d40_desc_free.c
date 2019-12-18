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
struct d40_desc {int dummy; } ;
struct d40_chan {TYPE_1__* base; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc_slab; } ;

/* Variables and functions */
 int /*<<< orphan*/  d40_lcla_free_all (struct d40_chan*,struct d40_desc*) ; 
 int /*<<< orphan*/  d40_pool_lli_free (struct d40_chan*,struct d40_desc*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct d40_desc*) ; 

__attribute__((used)) static void d40_desc_free(struct d40_chan *d40c, struct d40_desc *d40d)
{

	d40_pool_lli_free(d40c, d40d);
	d40_lcla_free_all(d40c, d40d);
	kmem_cache_free(d40c->base->desc_slab, d40d);
}