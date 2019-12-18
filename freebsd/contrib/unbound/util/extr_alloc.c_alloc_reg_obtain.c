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
struct regional {int /*<<< orphan*/ * next; } ;
struct alloc_cache {scalar_t__ num_reg_blocks; struct regional* reg_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_REG_SIZE ; 
 struct regional* regional_create_custom (int /*<<< orphan*/ ) ; 

struct regional* 
alloc_reg_obtain(struct alloc_cache* alloc)
{
	if(alloc->num_reg_blocks > 0) {
		struct regional* r = alloc->reg_list;
		alloc->reg_list = (struct regional*)r->next;
		r->next = NULL;
		alloc->num_reg_blocks--;
		return r;
	}
	return regional_create_custom(ALLOC_REG_SIZE);
}