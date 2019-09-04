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
typedef  int u32 ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_4__ {int enabled; int /*<<< orphan*/  topid; } ;
typedef  TYPE_1__ logfile_ctx_t ;
struct TYPE_5__ {TYPE_1__* logfile_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 

void logfile_generate_topid (hashcat_ctx_t *hashcat_ctx)
{
  logfile_ctx_t *logfile_ctx = hashcat_ctx->logfile_ctx;

  if (logfile_ctx->enabled == false) return;

  struct timeval v;

  gettimeofday (&v, NULL);

  snprintf (logfile_ctx->topid, 40, "TOP.%08x.%08x", (u32) v.tv_sec, (u32) v.tv_usec);
}