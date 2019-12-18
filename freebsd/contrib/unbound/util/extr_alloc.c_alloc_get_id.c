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
typedef  int uint64_t ;
struct alloc_cache {int next_id; int last_id; scalar_t__ thread_num; int /*<<< orphan*/  cleanup_arg; int /*<<< orphan*/  (* cleanup ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int THRNUM_SHIFT ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_alloc_cleanup (int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  log_warn (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

uint64_t
alloc_get_id(struct alloc_cache* alloc)
{
	uint64_t id = alloc->next_id++;
	if(id == alloc->last_id) {
		log_warn("rrset alloc: out of 64bit ids. Clearing cache.");
		fptr_ok(fptr_whitelist_alloc_cleanup(alloc->cleanup));
		(*alloc->cleanup)(alloc->cleanup_arg);

		/* start back at first number */   	/* like in alloc_init*/
		alloc->next_id = (uint64_t)alloc->thread_num; 	
		alloc->next_id <<= THRNUM_SHIFT; 	/* in steps for comp. */
		alloc->next_id += 1;			/* portability. */
		/* and generate new and safe id */
		id = alloc->next_id++;
	}
	return id;
}