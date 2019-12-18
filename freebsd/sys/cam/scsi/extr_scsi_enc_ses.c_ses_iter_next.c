#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ses_iterator {int global_element_index; size_t type_index; scalar_t__ type_element_index; TYPE_2__* cache; void* saved_individual_element_index; void* individual_element_index; } ;
struct TYPE_7__ {TYPE_1__* hdr; } ;
typedef  TYPE_3__ ses_type_t ;
struct TYPE_8__ {size_t ses_ntypes; TYPE_3__* ses_types; } ;
typedef  TYPE_4__ ses_cache_t ;
typedef  int /*<<< orphan*/  enc_element_t ;
struct TYPE_6__ {int /*<<< orphan*/ * elm_map; scalar_t__ nelms; TYPE_4__* private; } ;
struct TYPE_5__ {scalar_t__ etype_maxelt; } ;

/* Variables and functions */
 void* ITERATOR_INDEX_END ; 
 void* ITERATOR_INDEX_INVALID ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 

__attribute__((used)) static enc_element_t *
ses_iter_next(struct ses_iterator *iter)
{
	ses_cache_t	 *ses_cache;
	const ses_type_t *element_type;

	ses_cache = iter->cache->private;

	/*
	 * Note: Treat nelms as signed, so we will hit this case
	 *       and immediately terminate the iteration if the
	 *	 configuration has 0 objects.
	 */
	if (iter->global_element_index >= (int)iter->cache->nelms - 1) {

		/* Elements exhausted. */
		iter->type_index	       = ITERATOR_INDEX_END;
		iter->type_element_index       = ITERATOR_INDEX_END;
		iter->global_element_index     = ITERATOR_INDEX_END;
		iter->individual_element_index = ITERATOR_INDEX_END;
		iter->saved_individual_element_index = ITERATOR_INDEX_END;
		return (NULL);
	}

	KASSERT((iter->type_index < ses_cache->ses_ntypes),
		("Corrupted element iterator. %d not less than %d",
		 iter->type_index, ses_cache->ses_ntypes));

	element_type = &ses_cache->ses_types[iter->type_index];
	iter->global_element_index++;
	iter->type_element_index++;

	/*
	 * There is an object for overal type status in addition
	 * to one for each allowed element, but only if the element
	 * count is non-zero.
	 */
	if (iter->type_element_index > element_type->hdr->etype_maxelt) {

		/*
		 * We've exhausted the elements of this type.
		 * This next element belongs to the next type.
		 */
		iter->type_index++;
		iter->type_element_index = 0;
		iter->individual_element_index = ITERATOR_INDEX_INVALID;
	}

	if (iter->type_element_index > 0) {
		iter->individual_element_index =
		    ++iter->saved_individual_element_index;
	}

	return (&iter->cache->elm_map[iter->global_element_index]);
}