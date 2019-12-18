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
struct alloc_cache {int /*<<< orphan*/  num_quar; int /*<<< orphan*/ * quar; } ;
typedef  int /*<<< orphan*/  alloc_special_type ;

/* Variables and functions */
 int ALLOC_SPECIAL_MAX ; 
 int /*<<< orphan*/  alloc_set_special_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alloc_setup_special (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static void
prealloc_setup(struct alloc_cache* alloc)
{
	alloc_special_type* p;
	int i;
	for(i=0; i<ALLOC_SPECIAL_MAX; i++) {
		if(!(p = (alloc_special_type*)malloc(
			sizeof(alloc_special_type)))) {
			log_err("prealloc: out of memory");
			return;
		}
		alloc_setup_special(p);
		alloc_set_special_next(p, alloc->quar);
		alloc->quar = p;
		alloc->num_quar++;
	}
}