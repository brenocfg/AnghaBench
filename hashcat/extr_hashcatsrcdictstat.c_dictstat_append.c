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
struct TYPE_6__ {int dictstat_disable; } ;
typedef  TYPE_1__ hashconfig_t ;
struct TYPE_7__ {TYPE_3__* dictstat_ctx; TYPE_1__* hashconfig; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
typedef  int /*<<< orphan*/  dictstat_t ;
struct TYPE_8__ {int enabled; scalar_t__ cnt; int /*<<< orphan*/  base; int /*<<< orphan*/  filename; } ;
typedef  TYPE_3__ dictstat_ctx_t ;

/* Variables and functions */
 scalar_t__ MAX_DICTSTAT ; 
 int /*<<< orphan*/  event_log_error (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsearch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sort_by_dictstat ; 

void dictstat_append (hashcat_ctx_t *hashcat_ctx, dictstat_t *d)
{
  hashconfig_t   *hashconfig   = hashcat_ctx->hashconfig;
  dictstat_ctx_t *dictstat_ctx = hashcat_ctx->dictstat_ctx;

  if (dictstat_ctx->enabled == false) return;

  if (hashconfig->dictstat_disable == true) return;

  if (dictstat_ctx->cnt == MAX_DICTSTAT)
  {
    event_log_error (hashcat_ctx, "There are too many entries in the %s database. You have to remove/rename it.", dictstat_ctx->filename);

    return;
  }

  lsearch (d, dictstat_ctx->base, &dictstat_ctx->cnt, sizeof (dictstat_t), sort_by_dictstat);
}