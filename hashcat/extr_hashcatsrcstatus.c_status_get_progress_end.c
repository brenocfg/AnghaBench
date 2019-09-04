#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int slow_candidates; scalar_t__ limit; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_11__ {scalar_t__ attack_kern; } ;
typedef  TYPE_2__ user_options_extra_t ;
typedef  int u64 ;
struct TYPE_12__ {int kernel_rules_cnt; } ;
typedef  TYPE_3__ straight_ctx_t ;
struct TYPE_13__ {int words_cnt; int /*<<< orphan*/  words_base; } ;
typedef  TYPE_4__ status_ctx_t ;
struct TYPE_14__ {int bfs_cnt; } ;
typedef  TYPE_5__ mask_ctx_t ;
struct TYPE_15__ {int salts_cnt; } ;
typedef  TYPE_6__ hashes_t ;
struct TYPE_16__ {TYPE_3__* straight_ctx; TYPE_5__* mask_ctx; TYPE_8__* combinator_ctx; TYPE_2__* user_options_extra; TYPE_1__* user_options; TYPE_4__* status_ctx; TYPE_6__* hashes; } ;
typedef  TYPE_7__ hashcat_ctx_t ;
struct TYPE_17__ {int combs_cnt; } ;
typedef  TYPE_8__ combinator_ctx_t ;

/* Variables and functions */
 scalar_t__ ATTACK_KERN_BF ; 
 scalar_t__ ATTACK_KERN_COMBI ; 
 scalar_t__ ATTACK_KERN_STRAIGHT ; 
 int MIN (scalar_t__,int /*<<< orphan*/ ) ; 

u64 status_get_progress_end (const hashcat_ctx_t *hashcat_ctx)
{
  const hashes_t             *hashes             = hashcat_ctx->hashes;
  const status_ctx_t         *status_ctx         = hashcat_ctx->status_ctx;
  const user_options_t       *user_options       = hashcat_ctx->user_options;
  const user_options_extra_t *user_options_extra = hashcat_ctx->user_options_extra;

  u64 progress_end = status_ctx->words_cnt * hashes->salts_cnt;

  if (user_options->limit)
  {
    const combinator_ctx_t *combinator_ctx = hashcat_ctx->combinator_ctx;
    const mask_ctx_t       *mask_ctx       = hashcat_ctx->mask_ctx;
    const straight_ctx_t   *straight_ctx   = hashcat_ctx->straight_ctx;

    progress_end = MIN (user_options->limit, status_ctx->words_base) * hashes->salts_cnt;

    if (user_options->slow_candidates == true)
    {
      // nothing to do
    }
    else
    {
      if      (user_options_extra->attack_kern == ATTACK_KERN_STRAIGHT) progress_end  *= straight_ctx->kernel_rules_cnt;
      else if (user_options_extra->attack_kern == ATTACK_KERN_COMBI)    progress_end  *= combinator_ctx->combs_cnt;
      else if (user_options_extra->attack_kern == ATTACK_KERN_BF)       progress_end  *= mask_ctx->bfs_cnt;
    }
  }

  return progress_end;
}