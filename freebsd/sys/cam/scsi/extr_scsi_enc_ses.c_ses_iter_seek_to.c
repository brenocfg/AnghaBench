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
struct ses_iterator {int global_element_index; int individual_element_index; TYPE_1__* cache; } ;
typedef  scalar_t__ ses_elem_index_type_t ;
typedef  int /*<<< orphan*/  enc_element_t ;
struct TYPE_2__ {int /*<<< orphan*/ * elm_map; } ;

/* Variables and functions */
 scalar_t__ SES_ELEM_INDEX_GLOBAL ; 
 int /*<<< orphan*/ * ses_iter_next (struct ses_iterator*) ; 
 int /*<<< orphan*/  ses_iter_reset (struct ses_iterator*) ; 

__attribute__((used)) static enc_element_t *
ses_iter_seek_to(struct ses_iterator *iter, int element_index,
		 ses_elem_index_type_t index_type)
{
	enc_element_t	*element;
	int		*cur_index;

	if (index_type == SES_ELEM_INDEX_GLOBAL)
		cur_index = &iter->global_element_index;
	else
		cur_index = &iter->individual_element_index;

	if (*cur_index == element_index) {
		/* Already there. */
		return (&iter->cache->elm_map[iter->global_element_index]);
	}

	ses_iter_reset(iter);
	while ((element = ses_iter_next(iter)) != NULL
	    && *cur_index != element_index)
		;

	if (*cur_index != element_index)
		return (NULL);

	return (element);
}