#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct subpage_prot_table {int dummy; } ;
struct TYPE_11__ {scalar_t__ id; TYPE_4__* hash_context; } ;
struct mm_struct {TYPE_3__ context; } ;
struct hash_mm_context {int dummy; } ;
struct TYPE_14__ {TYPE_2__* mm; } ;
struct TYPE_13__ {scalar_t__ spt; } ;
struct TYPE_12__ {struct TYPE_12__* spt; } ;
struct TYPE_9__ {TYPE_6__* hash_context; } ;
struct TYPE_10__ {TYPE_1__ context; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_8__* current ; 
 int /*<<< orphan*/  kfree (TYPE_4__*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pkey_mm_init (struct mm_struct*) ; 
 int realloc_context_ids (TYPE_3__*) ; 
 int /*<<< orphan*/  slice_init_new_context_exec (struct mm_struct*) ; 

__attribute__((used)) static int hash__init_new_context(struct mm_struct *mm)
{
	int index;

	mm->context.hash_context = kmalloc(sizeof(struct hash_mm_context),
					   GFP_KERNEL);
	if (!mm->context.hash_context)
		return -ENOMEM;

	/*
	 * The old code would re-promote on fork, we don't do that when using
	 * slices as it could cause problem promoting slices that have been
	 * forced down to 4K.
	 *
	 * For book3s we have MMU_NO_CONTEXT set to be ~0. Hence check
	 * explicitly against context.id == 0. This ensures that we properly
	 * initialize context slice details for newly allocated mm's (which will
	 * have id == 0) and don't alter context slice inherited via fork (which
	 * will have id != 0).
	 *
	 * We should not be calling init_new_context() on init_mm. Hence a
	 * check against 0 is OK.
	 */
	if (mm->context.id == 0) {
		memset(mm->context.hash_context, 0, sizeof(struct hash_mm_context));
		slice_init_new_context_exec(mm);
	} else {
		/* This is fork. Copy hash_context details from current->mm */
		memcpy(mm->context.hash_context, current->mm->context.hash_context, sizeof(struct hash_mm_context));
#ifdef CONFIG_PPC_SUBPAGE_PROT
		/* inherit subpage prot detalis if we have one. */
		if (current->mm->context.hash_context->spt) {
			mm->context.hash_context->spt = kmalloc(sizeof(struct subpage_prot_table),
								GFP_KERNEL);
			if (!mm->context.hash_context->spt) {
				kfree(mm->context.hash_context);
				return -ENOMEM;
			}
		}
#endif
	}

	index = realloc_context_ids(&mm->context);
	if (index < 0) {
#ifdef CONFIG_PPC_SUBPAGE_PROT
		kfree(mm->context.hash_context->spt);
#endif
		kfree(mm->context.hash_context);
		return index;
	}

	pkey_mm_init(mm);
	return index;
}