#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * pfp; } ;
struct TYPE_6__ {int enabled; TYPE_5__ fp; } ;
typedef  TYPE_1__ potfile_ctx_t ;
struct TYPE_7__ {int potfile_disable; } ;
typedef  TYPE_2__ hashconfig_t ;
struct TYPE_8__ {TYPE_1__* potfile_ctx; TYPE_2__* hashconfig; } ;
typedef  TYPE_3__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  hc_fclose (TYPE_5__*) ; 

void potfile_read_close (hashcat_ctx_t *hashcat_ctx)
{
  hashconfig_t  *hashconfig  = hashcat_ctx->hashconfig;
  potfile_ctx_t *potfile_ctx = hashcat_ctx->potfile_ctx;

  if (potfile_ctx->enabled == false) return;

  if (hashconfig->potfile_disable == true) return;

  if (potfile_ctx->fp.pfp == NULL) return;

  hc_fclose (&potfile_ctx->fp);
}