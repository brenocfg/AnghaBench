#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bhnd_nvram_store {int dummy; } ;
struct TYPE_3__ {size_t count; size_t capacity; void** cookiep; } ;
typedef  TYPE_1__ bhnd_nvstore_index ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NVSTORE_LOCK_ASSERT (struct bhnd_nvram_store*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MA_OWNED ; 

int
bhnd_nvstore_index_append(struct bhnd_nvram_store *sc,
    bhnd_nvstore_index *index, void *cookiep)
{
	BHND_NVSTORE_LOCK_ASSERT(sc, MA_OWNED);

	if (index->count >= index->capacity)
		return (ENOMEM);

	index->cookiep[index->count] = cookiep;
	index->count++;
	return (0);
}