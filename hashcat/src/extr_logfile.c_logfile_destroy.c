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
struct TYPE_5__ {int enabled; int /*<<< orphan*/  subid; int /*<<< orphan*/  topid; int /*<<< orphan*/  logfile; } ;
typedef  TYPE_1__ logfile_ctx_t ;
struct TYPE_6__ {TYPE_1__* logfile_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  hcfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void logfile_destroy (hashcat_ctx_t *hashcat_ctx)
{
  logfile_ctx_t *logfile_ctx = hashcat_ctx->logfile_ctx;

  if (logfile_ctx->enabled == false) return;

  hcfree (logfile_ctx->logfile);
  hcfree (logfile_ctx->topid);
  hcfree (logfile_ctx->subid);

  memset (logfile_ctx, 0, sizeof (logfile_ctx_t));
}