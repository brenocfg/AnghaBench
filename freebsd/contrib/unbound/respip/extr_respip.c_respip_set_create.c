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
struct respip_set {int /*<<< orphan*/  ip_tree; int /*<<< orphan*/  region; } ;

/* Variables and functions */
 int /*<<< orphan*/  addr_tree_init (int /*<<< orphan*/ *) ; 
 struct respip_set* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct respip_set*) ; 
 int /*<<< orphan*/  regional_create () ; 

struct respip_set*
respip_set_create(void)
{
	struct respip_set* set = calloc(1, sizeof(*set));
	if(!set)
		return NULL;
	set->region = regional_create();
	if(!set->region) {
		free(set);
		return NULL;
	}
	addr_tree_init(&set->ip_tree);
	return set;
}