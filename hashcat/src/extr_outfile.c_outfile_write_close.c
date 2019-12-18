#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * pfp; } ;
struct TYPE_5__ {TYPE_4__ fp; } ;
typedef  TYPE_1__ outfile_ctx_t ;
struct TYPE_6__ {TYPE_1__* outfile_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  hc_fclose (TYPE_4__*) ; 

void outfile_write_close (hashcat_ctx_t *hashcat_ctx)
{
  outfile_ctx_t *outfile_ctx = hashcat_ctx->outfile_ctx;

  if (outfile_ctx->fp.pfp == NULL) return;

  hc_fclose (&outfile_ctx->fp);
}