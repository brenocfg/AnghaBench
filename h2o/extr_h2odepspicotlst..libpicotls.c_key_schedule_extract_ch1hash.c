#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {TYPE_1__* hashes; } ;
typedef  TYPE_2__ ptls_key_schedule_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* final ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_3__* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTLS_HASH_FINAL_MODE_RESET ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void key_schedule_extract_ch1hash(ptls_key_schedule_t *sched, uint8_t *hash)
{
    sched->hashes[0].ctx->final(sched->hashes[0].ctx, hash, PTLS_HASH_FINAL_MODE_RESET);
}