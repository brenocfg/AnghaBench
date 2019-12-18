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
struct autr_global_data {int /*<<< orphan*/  probe; } ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  probetree_cmp ; 
 int /*<<< orphan*/  rbtree_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct autr_global_data* autr_global_create(void)
{
	struct autr_global_data* global;
	global = (struct autr_global_data*)malloc(sizeof(*global));
	if(!global) 
		return NULL;
	rbtree_init(&global->probe, &probetree_cmp);
	return global;
}