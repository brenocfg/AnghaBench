#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_10__ {scalar_t__ dicts_pos; } ;
typedef  TYPE_1__ straight_ctx_t ;
struct TYPE_11__ {scalar_t__ words_cur; } ;
typedef  TYPE_2__ status_ctx_t ;
struct TYPE_12__ {size_t argc; char** argv; scalar_t__ words_cur; scalar_t__ dicts_pos; scalar_t__ masks_pos; } ;
typedef  TYPE_3__ restore_data_t ;
struct TYPE_13__ {int enabled; char* new_restore_file; TYPE_3__* rd; } ;
typedef  TYPE_4__ restore_ctx_t ;
struct TYPE_14__ {scalar_t__ masks_pos; } ;
typedef  TYPE_5__ mask_ctx_t ;
struct TYPE_15__ {TYPE_1__* straight_ctx; TYPE_2__* status_ctx; TYPE_4__* restore_ctx; TYPE_5__* mask_ctx; } ;
typedef  TYPE_6__ hashcat_ctx_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _IONBF ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  event_log_error (TYPE_6__*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hc_fwrite (TYPE_3__*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ setvbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_restore (hashcat_ctx_t *hashcat_ctx)
{
  const mask_ctx_t     *mask_ctx     = hashcat_ctx->mask_ctx;
  const restore_ctx_t  *restore_ctx  = hashcat_ctx->restore_ctx;
  const status_ctx_t   *status_ctx   = hashcat_ctx->status_ctx;
  const straight_ctx_t *straight_ctx = hashcat_ctx->straight_ctx;

  if (restore_ctx->enabled == false) return 0;

  restore_data_t *rd = restore_ctx->rd;

  rd->masks_pos = mask_ctx->masks_pos;
  rd->dicts_pos = straight_ctx->dicts_pos;
  rd->words_cur = status_ctx->words_cur;

  char *new_restore_file = restore_ctx->new_restore_file;

  FILE *fp = fopen (new_restore_file, "wb");

  if (fp == NULL)
  {
    event_log_error (hashcat_ctx, "%s: %s", new_restore_file, strerror (errno));

    return -1;
  }

  if (setvbuf (fp, NULL, _IONBF, 0))
  {
    event_log_error (hashcat_ctx, "setvbuf file '%s': %s", new_restore_file, strerror (errno));

    fclose (fp);

    return -1;
  }

  hc_fwrite (rd, sizeof (restore_data_t), 1, fp);

  for (u32 i = 0; i < rd->argc; i++)
  {
    fprintf (fp, "%s", rd->argv[i]);

    fputc ('\n', fp);
  }

  fflush (fp);

  fsync (fileno (fp));

  fclose (fp);

  rd->masks_pos = 0;
  rd->dicts_pos = 0;
  rd->words_cur = 0;

  return 0;
}