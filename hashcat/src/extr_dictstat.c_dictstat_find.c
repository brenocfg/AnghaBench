#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_8__ {int dictstat_disable; } ;
typedef  TYPE_1__ hashconfig_t ;
struct TYPE_9__ {TYPE_4__* dictstat_ctx; TYPE_1__* hashconfig; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
struct TYPE_10__ {int /*<<< orphan*/  cnt; } ;
typedef  TYPE_3__ dictstat_t ;
struct TYPE_11__ {int enabled; int /*<<< orphan*/  cnt; int /*<<< orphan*/  base; } ;
typedef  TYPE_4__ dictstat_ctx_t ;

/* Variables and functions */
 scalar_t__ lfind (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sort_by_dictstat ; 

u64 dictstat_find (hashcat_ctx_t *hashcat_ctx, dictstat_t *d)
{
  hashconfig_t   *hashconfig   = hashcat_ctx->hashconfig;
  dictstat_ctx_t *dictstat_ctx = hashcat_ctx->dictstat_ctx;

  if (dictstat_ctx->enabled == false) return 0;

  if (hashconfig->dictstat_disable == true) return 0;

  dictstat_t *d_cache = (dictstat_t *) lfind (d, dictstat_ctx->base, &dictstat_ctx->cnt, sizeof (dictstat_t), sort_by_dictstat);

  if (d_cache == NULL) return 0;

  return d_cache->cnt;
}