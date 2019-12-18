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
struct ses_iterator {void* saved_individual_element_index; void* individual_element_index; void* global_element_index; void* type_element_index; scalar_t__ type_index; } ;

/* Variables and functions */
 void* ITERATOR_INDEX_INVALID ; 

__attribute__((used)) static void
ses_iter_reset(struct ses_iterator *iter)
{
	/*
	 * Set our indexes to just before the first valid element
	 * of the first type (ITERATOR_INDEX_INVALID == -1).  This
	 * simplifies the implementation of ses_iter_next().
	 */
	iter->type_index                     = 0;
	iter->type_element_index             = ITERATOR_INDEX_INVALID;
	iter->global_element_index           = ITERATOR_INDEX_INVALID;
	iter->individual_element_index       = ITERATOR_INDEX_INVALID;
	iter->saved_individual_element_index = ITERATOR_INDEX_INVALID;
}