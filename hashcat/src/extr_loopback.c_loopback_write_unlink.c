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
struct TYPE_4__ {int enabled; int /*<<< orphan*/ * filename; } ;
typedef  TYPE_1__ loopback_ctx_t ;
struct TYPE_5__ {TYPE_1__* loopback_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ *) ; 

void loopback_write_unlink (hashcat_ctx_t *hashcat_ctx)
{
  loopback_ctx_t *loopback_ctx = hashcat_ctx->loopback_ctx;

  if (loopback_ctx->enabled == false) return;

  if (loopback_ctx->filename == NULL) return;

  unlink (loopback_ctx->filename);
}