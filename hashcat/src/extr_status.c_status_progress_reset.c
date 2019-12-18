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
struct TYPE_5__ {int /*<<< orphan*/  words_progress_restored; int /*<<< orphan*/  words_progress_rejected; int /*<<< orphan*/  words_progress_done; } ;
typedef  TYPE_1__ status_ctx_t ;
struct TYPE_6__ {int salts_cnt; } ;
typedef  TYPE_2__ hashes_t ;
struct TYPE_7__ {TYPE_2__* hashes; TYPE_1__* status_ctx; } ;
typedef  TYPE_3__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void status_progress_reset (hashcat_ctx_t *hashcat_ctx)
{
  status_ctx_t *status_ctx = hashcat_ctx->status_ctx;
  hashes_t     *hashes     = hashcat_ctx->hashes;

  memset (status_ctx->words_progress_done,     0, hashes->salts_cnt * sizeof (u64));
  memset (status_ctx->words_progress_rejected, 0, hashes->salts_cnt * sizeof (u64));
  memset (status_ctx->words_progress_restored, 0, hashes->salts_cnt * sizeof (u64));
}