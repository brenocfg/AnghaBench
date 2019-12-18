#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dmar_map_entry {scalar_t__ end; scalar_t__ free_down; } ;
struct dmar_gas_match_args {scalar_t__ size; scalar_t__ offset; TYPE_2__* common; TYPE_1__* entry; } ;
struct TYPE_4__ {scalar_t__ lowaddr; int /*<<< orphan*/  alignment; } ;
struct TYPE_3__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 scalar_t__ DMAR_PAGE_SIZE ; 
 int ENOMEM ; 
 struct dmar_map_entry* RB_LEFT (struct dmar_map_entry*,int /*<<< orphan*/ ) ; 
 struct dmar_map_entry* RB_RIGHT (struct dmar_map_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_gas_match_insert (struct dmar_gas_match_args*,struct dmar_map_entry*) ; 
 scalar_t__ dmar_gas_match_one (struct dmar_gas_match_args*,struct dmar_map_entry*,scalar_t__) ; 
 int /*<<< orphan*/  rb_entry ; 
 int /*<<< orphan*/  roundup2 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dmar_gas_lowermatch(struct dmar_gas_match_args *a, struct dmar_map_entry *prev)
{
	struct dmar_map_entry *l;
	int ret;

	if (prev->end < a->common->lowaddr) {
		a->entry->start = roundup2(prev->end + DMAR_PAGE_SIZE,
		    a->common->alignment);
		if (dmar_gas_match_one(a, prev, a->common->lowaddr)) {
			dmar_gas_match_insert(a, prev);
			return (0);
		}
	}
	if (prev->free_down < a->size + a->offset + DMAR_PAGE_SIZE)
		return (ENOMEM);
	l = RB_LEFT(prev, rb_entry);
	if (l != NULL) {
		ret = dmar_gas_lowermatch(a, l);
		if (ret == 0)
			return (0);
	}
	l = RB_RIGHT(prev, rb_entry);
	if (l != NULL)
		return (dmar_gas_lowermatch(a, l));
	return (ENOMEM);
}