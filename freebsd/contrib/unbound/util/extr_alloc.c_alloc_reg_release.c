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
struct regional {char* next; } ;
struct alloc_cache {scalar_t__ num_reg_blocks; scalar_t__ max_reg_blocks; struct regional* reg_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regional_destroy (struct regional*) ; 
 int /*<<< orphan*/  regional_free_all (struct regional*) ; 

void 
alloc_reg_release(struct alloc_cache* alloc, struct regional* r)
{
	if(alloc->num_reg_blocks >= alloc->max_reg_blocks) {
		regional_destroy(r);
		return;
	}
	if(!r) return;
	regional_free_all(r);
	log_assert(r->next == NULL);
	r->next = (char*)alloc->reg_list;
	alloc->reg_list = r;
	alloc->num_reg_blocks++;
}