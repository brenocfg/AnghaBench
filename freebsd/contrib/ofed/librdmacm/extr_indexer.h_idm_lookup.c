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
struct index_map {scalar_t__* array; } ;

/* Variables and functions */
 int IDX_MAX_INDEX ; 
 void* idm_at (struct index_map*,int) ; 
 size_t idx_array_index (int) ; 

__attribute__((used)) static inline void *idm_lookup(struct index_map *idm, int index)
{
	return ((index <= IDX_MAX_INDEX) && idm->array[idx_array_index(index)]) ?
		idm_at(idm, index) : NULL;
}