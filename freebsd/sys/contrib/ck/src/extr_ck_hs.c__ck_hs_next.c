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
struct ck_hs_map {scalar_t__ capacity; int /*<<< orphan*/ * entries; } ;
struct ck_hs_iterator {scalar_t__ offset; } ;
struct ck_hs {int mode; } ;

/* Variables and functions */
 void* CK_CC_DECONST_PTR (int /*<<< orphan*/ ) ; 
 void* CK_HS_EMPTY ; 
 int CK_HS_MODE_OBJECT ; 
 void* CK_HS_TOMBSTONE ; 
 void* CK_HS_VMA (void*) ; 

__attribute__((used)) static bool 
_ck_hs_next(struct ck_hs *hs, struct ck_hs_map *map, struct ck_hs_iterator *i, void **key)
{
	void *value;
	if (i->offset >= map->capacity)
		return false;

	do {
		value = CK_CC_DECONST_PTR(map->entries[i->offset]);
		if (value != CK_HS_EMPTY && value != CK_HS_TOMBSTONE) {
#ifdef CK_HS_PP
			if (hs->mode & CK_HS_MODE_OBJECT)
				value = CK_HS_VMA(value);
#else
			(void)hs; /* Avoid unused parameter warning. */
#endif
			i->offset++;
			*key = value;
			return true;
		}
	} while (++i->offset < map->capacity);

	return false;
}