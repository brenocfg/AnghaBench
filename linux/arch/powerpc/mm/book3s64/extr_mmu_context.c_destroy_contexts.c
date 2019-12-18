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
struct TYPE_3__ {int* extended_id; int /*<<< orphan*/  hash_context; } ;
typedef  TYPE_1__ mm_context_t ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_context_ida ; 

__attribute__((used)) static void destroy_contexts(mm_context_t *ctx)
{
	int index, context_id;

	for (index = 0; index < ARRAY_SIZE(ctx->extended_id); index++) {
		context_id = ctx->extended_id[index];
		if (context_id)
			ida_free(&mmu_context_ida, context_id);
	}
	kfree(ctx->hash_context);
}