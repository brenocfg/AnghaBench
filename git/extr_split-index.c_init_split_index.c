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
struct split_index {int refcount; } ;
struct index_state {struct split_index* split_index; } ;

/* Variables and functions */
 struct split_index* xcalloc (int,int) ; 

struct split_index *init_split_index(struct index_state *istate)
{
	if (!istate->split_index) {
		istate->split_index = xcalloc(1, sizeof(*istate->split_index));
		istate->split_index->refcount = 1;
	}
	return istate->split_index;
}