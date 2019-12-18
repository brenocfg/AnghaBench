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
struct spu_gang {int aff_flags; int /*<<< orphan*/ * aff_ref_spu; int /*<<< orphan*/  aff_sched_count; } ;
struct spu_context {struct spu_gang* gang; int /*<<< orphan*/  aff_list; } ;

/* Variables and functions */
 int AFF_MERGED ; 
 int AFF_OFFSETS_SET ; 
 int /*<<< orphan*/  aff_merge_remaining_ctxs (struct spu_gang*) ; 
 int /*<<< orphan*/  aff_set_offsets (struct spu_gang*) ; 
 int /*<<< orphan*/  aff_set_ref_point_location (struct spu_gang*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int has_affinity(struct spu_context *ctx)
{
	struct spu_gang *gang = ctx->gang;

	if (list_empty(&ctx->aff_list))
		return 0;

	if (atomic_read(&ctx->gang->aff_sched_count) == 0)
		ctx->gang->aff_ref_spu = NULL;

	if (!gang->aff_ref_spu) {
		if (!(gang->aff_flags & AFF_MERGED))
			aff_merge_remaining_ctxs(gang);
		if (!(gang->aff_flags & AFF_OFFSETS_SET))
			aff_set_offsets(gang);
		aff_set_ref_point_location(gang);
	}

	return gang->aff_ref_spu != NULL;
}