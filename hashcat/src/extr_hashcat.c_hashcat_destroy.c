#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  wl_data; int /*<<< orphan*/  user_options; int /*<<< orphan*/  user_options_extra; int /*<<< orphan*/  tuning_db; int /*<<< orphan*/  straight_ctx; int /*<<< orphan*/  status_ctx; int /*<<< orphan*/  restore_ctx; int /*<<< orphan*/  potfile_ctx; int /*<<< orphan*/  pidfile_ctx; int /*<<< orphan*/  outfile_ctx; int /*<<< orphan*/  outcheck_ctx; int /*<<< orphan*/  backend_ctx; int /*<<< orphan*/  module_ctx; int /*<<< orphan*/  mask_ctx; int /*<<< orphan*/  loopback_ctx; int /*<<< orphan*/  logfile_ctx; int /*<<< orphan*/  induct_ctx; int /*<<< orphan*/  hwmon_ctx; int /*<<< orphan*/  hashes; int /*<<< orphan*/  hashconfig; int /*<<< orphan*/  hashcat_user; int /*<<< orphan*/  folder_config; int /*<<< orphan*/  event_ctx; int /*<<< orphan*/  dictstat_ctx; int /*<<< orphan*/  debugfile_ctx; int /*<<< orphan*/  cpt_ctx; int /*<<< orphan*/  combinator_ctx; int /*<<< orphan*/  bitmap_ctx; } ;
typedef  TYPE_1__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  hcfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void hashcat_destroy (hashcat_ctx_t *hashcat_ctx)
{
  hcfree (hashcat_ctx->bitmap_ctx);
  hcfree (hashcat_ctx->combinator_ctx);
  hcfree (hashcat_ctx->cpt_ctx);
  hcfree (hashcat_ctx->debugfile_ctx);
  hcfree (hashcat_ctx->dictstat_ctx);
  hcfree (hashcat_ctx->event_ctx);
  hcfree (hashcat_ctx->folder_config);
  hcfree (hashcat_ctx->hashcat_user);
  hcfree (hashcat_ctx->hashconfig);
  hcfree (hashcat_ctx->hashes);
  hcfree (hashcat_ctx->hwmon_ctx);
  hcfree (hashcat_ctx->induct_ctx);
  hcfree (hashcat_ctx->logfile_ctx);
  hcfree (hashcat_ctx->loopback_ctx);
  hcfree (hashcat_ctx->mask_ctx);
  hcfree (hashcat_ctx->module_ctx);
  hcfree (hashcat_ctx->backend_ctx);
  hcfree (hashcat_ctx->outcheck_ctx);
  hcfree (hashcat_ctx->outfile_ctx);
  hcfree (hashcat_ctx->pidfile_ctx);
  hcfree (hashcat_ctx->potfile_ctx);
  hcfree (hashcat_ctx->restore_ctx);
  hcfree (hashcat_ctx->status_ctx);
  hcfree (hashcat_ctx->straight_ctx);
  hcfree (hashcat_ctx->tuning_db);
  hcfree (hashcat_ctx->user_options_extra);
  hcfree (hashcat_ctx->user_options);
  hcfree (hashcat_ctx->wl_data);

  memset (hashcat_ctx, 0, sizeof (hashcat_ctx_t));
}