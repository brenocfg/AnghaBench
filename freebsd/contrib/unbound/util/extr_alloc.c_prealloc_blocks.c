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
struct alloc_cache {int /*<<< orphan*/  num_reg_blocks; struct regional* reg_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_REG_SIZE ; 
 int /*<<< orphan*/  log_err (char*) ; 
 struct regional* regional_create_custom (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
prealloc_blocks(struct alloc_cache* alloc, size_t num)
{
	size_t i;
	struct regional* r;
	for(i=0; i<num; i++) {
		r = regional_create_custom(ALLOC_REG_SIZE);
		if(!r) {
			log_err("prealloc blocks: out of memory");
			return;
		}
		r->next = (char*)alloc->reg_list;
		alloc->reg_list = r;
		alloc->num_reg_blocks ++;
	}
}