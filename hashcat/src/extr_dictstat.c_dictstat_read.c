#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_7__ {int dictstat_disable; } ;
typedef  TYPE_1__ hashconfig_t ;
struct TYPE_8__ {TYPE_3__* dictstat_ctx; TYPE_1__* hashconfig; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
typedef  int dictstat_t ;
struct TYPE_9__ {int enabled; int /*<<< orphan*/  filename; int /*<<< orphan*/  cnt; int /*<<< orphan*/  base; } ;
typedef  TYPE_3__ dictstat_ctx_t ;
typedef  int /*<<< orphan*/  HCFILE ;

/* Variables and functions */
 int DICTSTAT_VERSION ; 
 int /*<<< orphan*/  MAX_DICTSTAT ; 
 int byte_swap_64 (int) ; 
 int /*<<< orphan*/  event_log_error (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_log_warning (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hc_fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hc_feof (int /*<<< orphan*/ *) ; 
 int hc_fopen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 size_t hc_fread (int*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsearch (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sort_by_dictstat ; 

void dictstat_read (hashcat_ctx_t *hashcat_ctx)
{
  hashconfig_t   *hashconfig   = hashcat_ctx->hashconfig;
  dictstat_ctx_t *dictstat_ctx = hashcat_ctx->dictstat_ctx;

  if (dictstat_ctx->enabled == false) return;

  if (hashconfig->dictstat_disable == true) return;

  HCFILE fp;

  if (hc_fopen (&fp, dictstat_ctx->filename, "rb") == false)
  {
    // first run, file does not exist, do not error out

    return;
  }

  // parse header

  u64 v;
  u64 z;

  const size_t nread1 = hc_fread (&v, sizeof (u64), 1, &fp);
  const size_t nread2 = hc_fread (&z, sizeof (u64), 1, &fp);

  if ((nread1 != 1) || (nread2 != 1))
  {
    event_log_error (hashcat_ctx, "%s: Invalid header", dictstat_ctx->filename);

    hc_fclose (&fp);

    return;
  }

  v = byte_swap_64 (v);
  z = byte_swap_64 (z);

  if ((v & 0xffffffffffffff00) != (DICTSTAT_VERSION & 0xffffffffffffff00))
  {
    event_log_error (hashcat_ctx, "%s: Invalid header, ignoring content", dictstat_ctx->filename);

    hc_fclose (&fp);

    return;
  }

  if (z != 0)
  {
    event_log_error (hashcat_ctx, "%s: Invalid header, ignoring content", dictstat_ctx->filename);

    hc_fclose (&fp);

    return;
  }

  if ((v & 0xff) < (DICTSTAT_VERSION & 0xff))
  {
    event_log_warning (hashcat_ctx, "%s: Outdated header version, ignoring content", dictstat_ctx->filename);

    hc_fclose (&fp);

    return;
  }

  // parse data

  while (!hc_feof (&fp))
  {
    dictstat_t d;

    const size_t nread = hc_fread (&d, sizeof (dictstat_t), 1, &fp);

    if (nread == 0) continue;

    lsearch (&d, dictstat_ctx->base, &dictstat_ctx->cnt, sizeof (dictstat_t), sort_by_dictstat);

    if (dictstat_ctx->cnt == MAX_DICTSTAT)
    {
      event_log_error (hashcat_ctx, "There are too many entries in the %s database. You have to remove/rename it.", dictstat_ctx->filename);

      break;
    }
  }

  hc_fclose (&fp);
}