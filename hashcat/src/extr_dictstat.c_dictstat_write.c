#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_6__ {int dictstat_disable; } ;
typedef  TYPE_1__ hashconfig_t ;
struct TYPE_7__ {TYPE_3__* dictstat_ctx; TYPE_1__* hashconfig; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
typedef  int /*<<< orphan*/  dictstat_t ;
struct TYPE_8__ {int enabled; int cnt; int /*<<< orphan*/ * base; int /*<<< orphan*/  filename; } ;
typedef  TYPE_3__ dictstat_ctx_t ;
typedef  int /*<<< orphan*/  HCFILE ;

/* Variables and functions */
 int /*<<< orphan*/  DICTSTAT_VERSION ; 
 int /*<<< orphan*/  byte_swap_64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  event_log_error (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hc_fclose (int /*<<< orphan*/ *) ; 
 int hc_fopen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hc_fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int hc_lockfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int dictstat_write (hashcat_ctx_t *hashcat_ctx)
{
  hashconfig_t   *hashconfig   = hashcat_ctx->hashconfig;
  dictstat_ctx_t *dictstat_ctx = hashcat_ctx->dictstat_ctx;

  if (dictstat_ctx->enabled == false) return 0;

  if (hashconfig->dictstat_disable == true) return 0;

  HCFILE fp;

  if (hc_fopen (&fp, dictstat_ctx->filename, "wb") == false)
  {
    event_log_error (hashcat_ctx, "%s: %s", dictstat_ctx->filename, strerror (errno));

    return -1;
  }

  if (hc_lockfile (&fp) == -1)
  {
    hc_fclose (&fp);

    event_log_error (hashcat_ctx, "%s: %s", dictstat_ctx->filename, strerror (errno));

    return -1;
  }

  // header

  u64 v = DICTSTAT_VERSION;
  u64 z = 0;

  v = byte_swap_64 (v);
  z = byte_swap_64 (z);

  hc_fwrite (&v, sizeof (u64), 1, &fp);
  hc_fwrite (&z, sizeof (u64), 1, &fp);

  // data

  hc_fwrite (dictstat_ctx->base, sizeof (dictstat_t), dictstat_ctx->cnt, &fp);

  hc_fclose (&fp);

  return 0;
}