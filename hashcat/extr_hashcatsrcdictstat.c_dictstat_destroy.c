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
struct TYPE_8__ {int enabled; int /*<<< orphan*/  base; int /*<<< orphan*/  filename; } ;
typedef  TYPE_3__ dictstat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  hcfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

void dictstat_destroy (hashcat_ctx_t *hashcat_ctx)
{
  hashconfig_t   *hashconfig   = hashcat_ctx->hashconfig;
  dictstat_ctx_t *dictstat_ctx = hashcat_ctx->dictstat_ctx;

  if (dictstat_ctx->enabled == false) return;

  if (hashconfig->dictstat_disable == true) return;

  hcfree (dictstat_ctx->filename);
  hcfree (dictstat_ctx->base);

  memset (dictstat_ctx, 0, sizeof (dictstat_ctx_t));
}