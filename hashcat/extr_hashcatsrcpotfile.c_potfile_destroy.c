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
struct TYPE_6__ {int enabled; int /*<<< orphan*/  tmp_buf; int /*<<< orphan*/  out_buf; } ;
typedef  TYPE_1__ potfile_ctx_t ;
struct TYPE_7__ {int potfile_disable; } ;
typedef  TYPE_2__ hashconfig_t ;
struct TYPE_8__ {TYPE_1__* potfile_ctx; TYPE_2__* hashconfig; } ;
typedef  TYPE_3__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  hcfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void potfile_destroy (hashcat_ctx_t *hashcat_ctx)
{
  hashconfig_t  *hashconfig  = hashcat_ctx->hashconfig;
  potfile_ctx_t *potfile_ctx = hashcat_ctx->potfile_ctx;

  if (potfile_ctx->enabled == false) return;

  if (hashconfig->potfile_disable == true) return;

  hcfree (potfile_ctx->out_buf);
  hcfree (potfile_ctx->tmp_buf);

  memset (potfile_ctx, 0, sizeof (potfile_ctx_t));
}