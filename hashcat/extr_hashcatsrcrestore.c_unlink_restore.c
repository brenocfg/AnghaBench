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
struct TYPE_5__ {scalar_t__ devices_status; int run_thread_level1; } ;
typedef  TYPE_1__ status_ctx_t ;
struct TYPE_6__ {int enabled; int /*<<< orphan*/  new_restore_file; int /*<<< orphan*/  eff_restore_file; } ;
typedef  TYPE_2__ restore_ctx_t ;
struct TYPE_7__ {TYPE_1__* status_ctx; TYPE_2__* restore_ctx; } ;
typedef  TYPE_3__ hashcat_ctx_t ;

/* Variables and functions */
 scalar_t__ STATUS_CRACKED ; 
 scalar_t__ STATUS_EXHAUSTED ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

void unlink_restore (hashcat_ctx_t *hashcat_ctx)
{
  restore_ctx_t *restore_ctx = hashcat_ctx->restore_ctx;
  status_ctx_t  *status_ctx  = hashcat_ctx->status_ctx;

  if (restore_ctx->enabled == false) return;

  if ((status_ctx->devices_status == STATUS_EXHAUSTED) && (status_ctx->run_thread_level1 == true)) // this is to check for [c]heckpoint
  {
    unlink (restore_ctx->eff_restore_file);
    unlink (restore_ctx->new_restore_file);
  }

  if (status_ctx->devices_status == STATUS_CRACKED)
  {
    unlink (restore_ctx->eff_restore_file);
    unlink (restore_ctx->new_restore_file);
  }
}