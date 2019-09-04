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
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct TYPE_5__ {scalar_t__* words_progress_rejected; } ;
typedef  TYPE_1__ status_ctx_t ;
struct TYPE_6__ {size_t salts_cnt; } ;
typedef  TYPE_2__ hashes_t ;
struct TYPE_7__ {TYPE_1__* status_ctx; TYPE_2__* hashes; } ;
typedef  TYPE_3__ hashcat_ctx_t ;

/* Variables and functions */

u64 status_get_progress_rejected (const hashcat_ctx_t *hashcat_ctx)
{
  const hashes_t     *hashes     = hashcat_ctx->hashes;
  const status_ctx_t *status_ctx = hashcat_ctx->status_ctx;

  u64 progress_rejected = 0;

  for (u32 salt_pos = 0; salt_pos < hashes->salts_cnt; salt_pos++)
  {
    progress_rejected += status_ctx->words_progress_rejected[salt_pos];
  }

  return progress_rejected;
}