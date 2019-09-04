#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* cpt_ctx; } ;
typedef  TYPE_1__ hashcat_ctx_t ;
typedef  int /*<<< orphan*/  cpt_t ;
struct TYPE_5__ {int enabled; int /*<<< orphan*/  cpt_start; scalar_t__ cpt_pos; scalar_t__ cpt_total; int /*<<< orphan*/  cpt_buf; } ;
typedef  TYPE_2__ cpt_ctx_t ;

/* Variables and functions */
 int CPT_CACHE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void cpt_ctx_reset (hashcat_ctx_t *hashcat_ctx)
{
  cpt_ctx_t *cpt_ctx = hashcat_ctx->cpt_ctx;

  if (cpt_ctx->enabled == false) return;

  memset (cpt_ctx->cpt_buf, 0, CPT_CACHE * sizeof (cpt_t));

  cpt_ctx->cpt_total = 0;
  cpt_ctx->cpt_pos   = 0;
  cpt_ctx->cpt_start = time (NULL);
}