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
typedef  int /*<<< orphan*/  pidfile_data_t ;
struct TYPE_5__ {char* filename; int /*<<< orphan*/ * pd; } ;
typedef  TYPE_1__ pidfile_ctx_t ;
struct TYPE_6__ {TYPE_1__* pidfile_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
typedef  int /*<<< orphan*/  HCFILE ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  event_log_error (TYPE_2__*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hc_fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hc_fflush (int /*<<< orphan*/ *) ; 
 int hc_fopen (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  hc_fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_pidfile (hashcat_ctx_t *hashcat_ctx)
{
  const pidfile_ctx_t *pidfile_ctx = hashcat_ctx->pidfile_ctx;

  pidfile_data_t *pd = pidfile_ctx->pd;

  char *pidfile_filename = pidfile_ctx->filename;

  HCFILE fp;

  if (hc_fopen (&fp, pidfile_filename, "wb") == false)
  {
    event_log_error (hashcat_ctx, "%s: %s", pidfile_filename, strerror (errno));

    return -1;
  }

  hc_fwrite (pd, sizeof (pidfile_data_t), 1, &fp);

  hc_fflush (&fp);

  hc_fclose (&fp);

  return 0;
}