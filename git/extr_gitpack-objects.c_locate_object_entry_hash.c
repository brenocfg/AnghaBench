#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct packing_data {size_t index_size; scalar_t__* index; TYPE_3__* objects; } ;
struct TYPE_4__ {int /*<<< orphan*/  hash; } ;
struct TYPE_5__ {TYPE_1__ oid; } ;
struct TYPE_6__ {TYPE_2__ idx; } ;

/* Variables and functions */
 scalar_t__ hasheq (unsigned char const*,int /*<<< orphan*/ ) ; 
 size_t sha1hash (unsigned char const*) ; 

__attribute__((used)) static uint32_t locate_object_entry_hash(struct packing_data *pdata,
					 const unsigned char *sha1,
					 int *found)
{
	uint32_t i, mask = (pdata->index_size - 1);

	i = sha1hash(sha1) & mask;

	while (pdata->index[i] > 0) {
		uint32_t pos = pdata->index[i] - 1;

		if (hasheq(sha1, pdata->objects[pos].idx.oid.hash)) {
			*found = 1;
			return i;
		}

		i = (i + 1) & mask;
	}

	*found = 0;
	return i;
}