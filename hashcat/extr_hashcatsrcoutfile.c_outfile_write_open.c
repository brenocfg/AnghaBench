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
struct TYPE_5__ {int /*<<< orphan*/ * fp; int /*<<< orphan*/ * filename; } ;
typedef  TYPE_1__ outfile_ctx_t ;
struct TYPE_6__ {TYPE_1__* outfile_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  event_log_error (TYPE_2__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ *,char*) ; 
 int lock_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int outfile_write_open (hashcat_ctx_t *hashcat_ctx)
{
  outfile_ctx_t *outfile_ctx = hashcat_ctx->outfile_ctx;

  if (outfile_ctx->filename == NULL) return 0;

  FILE *fp = fopen (outfile_ctx->filename, "ab");

  if (fp == NULL)
  {
    event_log_error (hashcat_ctx, "%s: %s", outfile_ctx->filename, strerror (errno));

    return -1;
  }

  if (lock_file (fp) == -1)
  {
    fclose (fp);

    event_log_error (hashcat_ctx, "%s: %s", outfile_ctx->filename, strerror (errno));

    return -1;
  }

  outfile_ctx->fp = fp;

  return 0;
}