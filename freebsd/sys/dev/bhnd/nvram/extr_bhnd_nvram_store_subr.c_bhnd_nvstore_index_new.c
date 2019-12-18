#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bhnd_nvstore_index {int dummy; } ;
struct TYPE_4__ {size_t capacity; scalar_t__ count; } ;
typedef  TYPE_1__ bhnd_nvstore_index ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NV_LOG (char*,size_t) ; 
 TYPE_1__* bhnd_nv_malloc (size_t) ; 

bhnd_nvstore_index *
bhnd_nvstore_index_new(size_t capacity)
{
	bhnd_nvstore_index	*index;
	size_t			 bytes;

	/* Allocate and populate variable index */
	bytes = sizeof(struct bhnd_nvstore_index) + (sizeof(void *) * capacity);
	index = bhnd_nv_malloc(bytes);
	if (index == NULL) {
		BHND_NV_LOG("error allocating %zu byte index\n", bytes);
		return (NULL);
	}

	index->count = 0;
	index->capacity = capacity;

	return (index);
}