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
struct TYPE_5__ {TYPE_2__* cpt_ctx; } ;
typedef  TYPE_1__ hashcat_ctx_t ;
struct TYPE_6__ {int enabled; int /*<<< orphan*/  cpt_buf; } ;
typedef  TYPE_2__ cpt_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  hcfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void cpt_ctx_destroy (hashcat_ctx_t *hashcat_ctx)
{
  cpt_ctx_t *cpt_ctx = hashcat_ctx->cpt_ctx;

  if (cpt_ctx->enabled == false) return;

  hcfree (cpt_ctx->cpt_buf);

  memset (cpt_ctx, 0, sizeof (cpt_ctx_t));
}