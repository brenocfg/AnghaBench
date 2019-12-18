#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int enabled; int /*<<< orphan*/  rd; int /*<<< orphan*/  new_restore_file; int /*<<< orphan*/  eff_restore_file; } ;
typedef  TYPE_1__ restore_ctx_t ;
struct TYPE_6__ {TYPE_1__* restore_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  hcfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void restore_ctx_destroy (hashcat_ctx_t *hashcat_ctx)
{
  restore_ctx_t *restore_ctx = hashcat_ctx->restore_ctx;

  if (restore_ctx->enabled == false) return;

  hcfree (restore_ctx->eff_restore_file);
  hcfree (restore_ctx->new_restore_file);
  hcfree (restore_ctx->rd);

  memset (restore_ctx, 0, sizeof (restore_ctx_t));
}