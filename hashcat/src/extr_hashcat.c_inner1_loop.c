#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_9__ {scalar_t__ dicts_pos; scalar_t__ dicts_cnt; } ;
typedef  TYPE_1__ straight_ctx_t ;
struct TYPE_10__ {int run_main_level3; int run_thread_level1; int run_thread_level2; } ;
typedef  TYPE_2__ status_ctx_t ;
struct TYPE_11__ {scalar_t__ dicts_pos; } ;
typedef  TYPE_3__ restore_data_t ;
struct TYPE_12__ {TYPE_3__* rd; } ;
typedef  TYPE_4__ restore_ctx_t ;
struct TYPE_13__ {TYPE_1__* straight_ctx; TYPE_2__* status_ctx; TYPE_4__* restore_ctx; } ;
typedef  TYPE_5__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVENT_INNERLOOP2_FINISHED ; 
 int /*<<< orphan*/  EVENT_INNERLOOP2_STARTING ; 
 int inner2_loop (TYPE_5__*) ; 
 int /*<<< orphan*/  myabort (TYPE_5__*) ; 

__attribute__((used)) static int inner1_loop (hashcat_ctx_t *hashcat_ctx)
{
  restore_ctx_t  *restore_ctx   = hashcat_ctx->restore_ctx;
  status_ctx_t   *status_ctx    = hashcat_ctx->status_ctx;
  straight_ctx_t *straight_ctx  = hashcat_ctx->straight_ctx;

  //status_ctx->run_main_level1   = true;
  //status_ctx->run_main_level2   = true;
  status_ctx->run_main_level3   = true;
  status_ctx->run_thread_level1 = true;
  status_ctx->run_thread_level2 = true;

  /**
   * loop through wordlists
   */

  EVENT (EVENT_INNERLOOP2_STARTING);

  if (restore_ctx->rd)
  {
    restore_data_t *rd = restore_ctx->rd;

    if (rd->dicts_pos > 0)
    {
      straight_ctx->dicts_pos = rd->dicts_pos;

      rd->dicts_pos = 0;
    }
  }

  if (straight_ctx->dicts_cnt)
  {
    for (u32 dicts_pos = straight_ctx->dicts_pos; dicts_pos < straight_ctx->dicts_cnt; dicts_pos++)
    {
      straight_ctx->dicts_pos = dicts_pos;

      if (inner2_loop (hashcat_ctx) == -1) myabort (hashcat_ctx);

      if (status_ctx->run_main_level3 == false) break;
    }

    if (status_ctx->run_main_level3 == true)
    {
      if (straight_ctx->dicts_pos + 1 == straight_ctx->dicts_cnt) straight_ctx->dicts_pos = 0;
    }
  }
  else
  {
    if (inner2_loop (hashcat_ctx) == -1) myabort (hashcat_ctx);
  }

  EVENT (EVENT_INNERLOOP2_FINISHED);

  return 0;
}