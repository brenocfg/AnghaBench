#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t num_hashes; TYPE_1__* hashes; int /*<<< orphan*/  secret; } ;
typedef  TYPE_2__ ptls_key_schedule_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* final ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_3__* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTLS_HASH_FINAL_MODE_FREE ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  ptls_clear_memory (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void key_schedule_free(ptls_key_schedule_t *sched)
{
    size_t i;
    ptls_clear_memory(sched->secret, sizeof(sched->secret));
    for (i = 0; i != sched->num_hashes; ++i)
        sched->hashes[i].ctx->final(sched->hashes[i].ctx, NULL, PTLS_HASH_FINAL_MODE_FREE);
    free(sched);
}