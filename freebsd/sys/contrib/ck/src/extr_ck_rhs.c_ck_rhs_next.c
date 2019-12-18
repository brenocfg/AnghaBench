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
struct ck_rhs_map {scalar_t__ capacity; } ;
struct ck_rhs_iterator {scalar_t__ offset; } ;
struct ck_rhs {int mode; struct ck_rhs_map* map; } ;

/* Variables and functions */
 void* CK_CC_DECONST_PTR (int /*<<< orphan*/ ) ; 
 void* CK_RHS_EMPTY ; 
 int CK_RHS_MODE_OBJECT ; 
 void* CK_RHS_VMA (void*) ; 
 int /*<<< orphan*/  ck_rhs_entry (struct ck_rhs_map*,scalar_t__) ; 

bool
ck_rhs_next(struct ck_rhs *hs, struct ck_rhs_iterator *i, void **key)
{
	struct ck_rhs_map *map = hs->map;
	void *value;

	if (i->offset >= map->capacity)
		return false;

	do {
		value = CK_CC_DECONST_PTR(ck_rhs_entry(map, i->offset));
		if (value != CK_RHS_EMPTY) {
#ifdef CK_RHS_PP
			if (hs->mode & CK_RHS_MODE_OBJECT)
				value = CK_RHS_VMA(value);
#endif
			i->offset++;
			*key = value;
			return true;
		}
	} while (++i->offset < map->capacity);

	return false;
}