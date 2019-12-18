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
struct TYPE_5__ {int /*<<< orphan*/ * filename; int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ outfile_ctx_t ;
struct TYPE_6__ {TYPE_1__* outfile_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  event_log_error (TYPE_2__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hc_fclose (int /*<<< orphan*/ *) ; 
 int hc_fopen (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int hc_lockfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int outfile_write_open (hashcat_ctx_t *hashcat_ctx)
{
  outfile_ctx_t *outfile_ctx = hashcat_ctx->outfile_ctx;

  if (outfile_ctx->filename == NULL) return 0;

  if (hc_fopen (&outfile_ctx->fp, outfile_ctx->filename, "ab") == false)
  {
    event_log_error (hashcat_ctx, "%s: %s", outfile_ctx->filename, strerror (errno));

    return -1;
  }

  if (hc_lockfile (&outfile_ctx->fp) == -1)
  {
    hc_fclose (&outfile_ctx->fp);

    event_log_error (hashcat_ctx, "%s: %s", outfile_ctx->filename, strerror (errno));

    return -1;
  }

  return 0;
}