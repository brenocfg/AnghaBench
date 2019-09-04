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
struct TYPE_2__ {int /*<<< orphan*/ * items; scalar_t__ alloc; scalar_t__ nr; } ;
struct config_set {int hash_initialized; TYPE_1__ list; int /*<<< orphan*/  config_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_set_element_cmp ; 
 int /*<<< orphan*/  hashmap_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void git_configset_init(struct config_set *cs)
{
	hashmap_init(&cs->config_hash, config_set_element_cmp, NULL, 0);
	cs->hash_initialized = 1;
	cs->list.nr = 0;
	cs->list.alloc = 0;
	cs->list.items = NULL;
}