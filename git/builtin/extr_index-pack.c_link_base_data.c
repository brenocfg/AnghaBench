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
struct base_data {scalar_t__ size; scalar_t__ data; struct base_data* child; struct base_data* base; } ;
struct TYPE_2__ {int /*<<< orphan*/  base_cache_used; struct base_data* base_cache; } ;

/* Variables and functions */
 TYPE_1__* get_thread_data () ; 
 int /*<<< orphan*/  prune_base_data (struct base_data*) ; 

__attribute__((used)) static void link_base_data(struct base_data *base, struct base_data *c)
{
	if (base)
		base->child = c;
	else
		get_thread_data()->base_cache = c;

	c->base = base;
	c->child = NULL;
	if (c->data)
		get_thread_data()->base_cache_used += c->size;
	prune_base_data(c);
}