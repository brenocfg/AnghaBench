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
struct TYPE_5__ {int /*<<< orphan*/ * mask; } ;
typedef  TYPE_1__ mask_ctx_t ;
struct TYPE_6__ {int /*<<< orphan*/  opts_type; } ;
typedef  TYPE_2__ hashconfig_t ;
struct TYPE_7__ {TYPE_1__* mask_ctx; TYPE_2__* hashconfig; } ;
typedef  TYPE_3__ hashcat_ctx_t ;

/* Variables and functions */
 int mp_get_length (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int status_get_guess_mask_length (const hashcat_ctx_t *hashcat_ctx)
{
  const hashconfig_t *hashconfig = hashcat_ctx->hashconfig;
  const mask_ctx_t   *mask_ctx   = hashcat_ctx->mask_ctx;

  if (mask_ctx == NULL) return -1;

  if (mask_ctx->mask == NULL) return -1;

  return mp_get_length (mask_ctx->mask, hashconfig->opts_type);
}