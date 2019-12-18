#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * pfp; } ;
struct TYPE_6__ {int enabled; int unused; TYPE_5__ fp; } ;
typedef  TYPE_1__ loopback_ctx_t ;
struct TYPE_7__ {TYPE_1__* loopback_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  hc_fclose (TYPE_5__*) ; 
 int /*<<< orphan*/  loopback_write_unlink (TYPE_2__*) ; 

void loopback_write_close (hashcat_ctx_t *hashcat_ctx)
{
  loopback_ctx_t *loopback_ctx = hashcat_ctx->loopback_ctx;

  if (loopback_ctx->enabled == false) return;

  if (loopback_ctx->fp.pfp == NULL) return;

  hc_fclose (&loopback_ctx->fp);

  if (loopback_ctx->unused == true)
  {
    loopback_write_unlink (hashcat_ctx);
  }
}