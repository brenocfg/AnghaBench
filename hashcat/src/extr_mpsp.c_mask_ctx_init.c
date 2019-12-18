#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int example_hashes; int left; int backend_info; int show; int usage; int version; scalar_t__ attack_mode; int benchmark; scalar_t__ custom_charset_4; scalar_t__ custom_charset_3; scalar_t__ custom_charset_2; scalar_t__ custom_charset_1; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_12__ {int hc_workc; char** hc_workv; } ;
typedef  TYPE_2__ user_options_extra_t ;
typedef  int /*<<< orphan*/  mf_t ;
struct TYPE_13__ {int enabled; int mask_from_file; scalar_t__ masks_cnt; int /*<<< orphan*/ * masks; int /*<<< orphan*/  mask; int /*<<< orphan*/ * mp_usr; int /*<<< orphan*/ * mp_sys; int /*<<< orphan*/ * mfs; scalar_t__ masks_pos; int /*<<< orphan*/ * markov_css_buf; int /*<<< orphan*/ * root_css_buf; int /*<<< orphan*/ * markov_table_buf; int /*<<< orphan*/ * root_table_buf; scalar_t__ css_cnt; int /*<<< orphan*/ * css_buf; } ;
typedef  TYPE_3__ mask_ctx_t ;
typedef  int /*<<< orphan*/  hcstat_table_t ;
struct TYPE_14__ {char* benchmark_mask; } ;
typedef  TYPE_4__ hashconfig_t ;
struct TYPE_15__ {TYPE_3__* mask_ctx; TYPE_1__* user_options; TYPE_2__* user_options_extra; TYPE_4__* hashconfig; } ;
typedef  TYPE_5__ hashcat_ctx_t ;
typedef  int /*<<< orphan*/  cs_t ;
typedef  int /*<<< orphan*/  HCFILE ;

/* Variables and functions */
 scalar_t__ ATTACK_MODE_BF ; 
 scalar_t__ ATTACK_MODE_COMBI ; 
 scalar_t__ ATTACK_MODE_HYBRID1 ; 
 scalar_t__ ATTACK_MODE_HYBRID2 ; 
 scalar_t__ ATTACK_MODE_STRAIGHT ; 
 int CHARSIZ ; 
 char* DEF_MASK ; 
 int /*<<< orphan*/  HCBUFSIZ_LARGE ; 
 int MAX_MFS ; 
 int SP_MARKOV_CNT ; 
 int SP_PW_MAX ; 
 int SP_ROOT_CNT ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  event_log_error (TYPE_5__*,char*,...) ; 
 size_t fgetl (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hc_fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hc_feof (int /*<<< orphan*/ *) ; 
 int hc_fopen (int /*<<< orphan*/ *,char*,char*) ; 
 int hc_path_exist (char*) ; 
 int hc_path_is_file (char*) ; 
 scalar_t__ hccalloc (int,int) ; 
 int /*<<< orphan*/  hcfree (char*) ; 
 scalar_t__ hcmalloc (int /*<<< orphan*/ ) ; 
 int mask_append (TYPE_5__*,char const*,char*) ; 
 char* mask_ctx_parse_maskfile_find_mask (char*,size_t const) ; 
 int /*<<< orphan*/  mp_setup_sys (int /*<<< orphan*/ *) ; 
 int mp_setup_usr (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int sp_setup_tbl (TYPE_5__*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int mask_ctx_init (hashcat_ctx_t *hashcat_ctx)
{
  const hashconfig_t         *hashconfig          = hashcat_ctx->hashconfig;
  const user_options_extra_t *user_options_extra  = hashcat_ctx->user_options_extra;
  const user_options_t       *user_options        = hashcat_ctx->user_options;
  mask_ctx_t                 *mask_ctx            = hashcat_ctx->mask_ctx;

  mask_ctx->enabled = false;

  if (user_options->example_hashes == true) return 0;
  if (user_options->left           == true) return 0;
  if (user_options->backend_info   == true) return 0;
  if (user_options->show           == true) return 0;
  if (user_options->usage          == true) return 0;
  if (user_options->version        == true) return 0;

  if (user_options->attack_mode == ATTACK_MODE_STRAIGHT) return 0;
  if (user_options->attack_mode == ATTACK_MODE_COMBI)    return 0;

  mask_ctx->enabled = true;

  mask_ctx->mp_sys  = (cs_t *) hccalloc (8, sizeof (cs_t));
  mask_ctx->mp_usr  = (cs_t *) hccalloc (4, sizeof (cs_t));

  mask_ctx->css_buf = (cs_t *) hccalloc (256, sizeof (cs_t));
  mask_ctx->css_cnt = 0;

  mask_ctx->root_table_buf   = (hcstat_table_t *) hccalloc (SP_ROOT_CNT,   sizeof (hcstat_table_t));
  mask_ctx->markov_table_buf = (hcstat_table_t *) hccalloc (SP_MARKOV_CNT, sizeof (hcstat_table_t));

  if (sp_setup_tbl (hashcat_ctx) == -1) return -1;

  mask_ctx->root_css_buf   = (cs_t *) hccalloc (SP_PW_MAX,           sizeof (cs_t));
  mask_ctx->markov_css_buf = (cs_t *) hccalloc (SP_PW_MAX * CHARSIZ, sizeof (cs_t));

  mask_ctx->mask_from_file = false;

  mask_ctx->masks     = NULL;
  mask_ctx->masks_pos = 0;
  mask_ctx->masks_cnt = 0;

  mask_ctx->mfs = (mf_t *) hccalloc (MAX_MFS, sizeof (mf_t));

  mp_setup_sys (mask_ctx->mp_sys);

  if (user_options->custom_charset_1) { if (mp_setup_usr (hashcat_ctx, mask_ctx->mp_sys, mask_ctx->mp_usr, user_options->custom_charset_1, 0) == -1) return -1; }
  if (user_options->custom_charset_2) { if (mp_setup_usr (hashcat_ctx, mask_ctx->mp_sys, mask_ctx->mp_usr, user_options->custom_charset_2, 1) == -1) return -1; }
  if (user_options->custom_charset_3) { if (mp_setup_usr (hashcat_ctx, mask_ctx->mp_sys, mask_ctx->mp_usr, user_options->custom_charset_3, 2) == -1) return -1; }
  if (user_options->custom_charset_4) { if (mp_setup_usr (hashcat_ctx, mask_ctx->mp_sys, mask_ctx->mp_usr, user_options->custom_charset_4, 3) == -1) return -1; }

  if (user_options->attack_mode == ATTACK_MODE_BF)
  {
    if (user_options->benchmark == false)
    {
      if (user_options_extra->hc_workc)
      {
        char *arg = user_options_extra->hc_workv[0];

        if (hc_path_exist (arg) == false)
        {
          if (mask_append (hashcat_ctx, arg, NULL) == -1) return -1;
        }
        else
        {
          mask_ctx->mask_from_file = true;

          for (int i = 0; i < user_options_extra->hc_workc; i++)
          {
            arg = user_options_extra->hc_workv[i];

            if (hc_path_is_file (arg) == true)
            {
              HCFILE mask_fp;

              if (hc_fopen (&mask_fp, arg, "r") == false)
              {
                event_log_error (hashcat_ctx, "%s: %s", arg, strerror (errno));

                return -1;
              }

              char *line_buf = (char *) hcmalloc (HCBUFSIZ_LARGE);

              while (!hc_feof (&mask_fp))
              {
                const size_t line_len = fgetl (&mask_fp, line_buf, HCBUFSIZ_LARGE);

                if (line_len == 0) continue;

                if (line_buf[0] == '#') continue;

                char *mask_buf = mask_ctx_parse_maskfile_find_mask (line_buf, line_len);

                char *prepend_buf = NULL;

                if (line_buf != mask_buf)
                {
                  // if we have custom charsets

                  prepend_buf = line_buf;

                  mask_buf[-1] = 0;
                }

                if (mask_append (hashcat_ctx, mask_buf, prepend_buf) == -1)
                {
                  hc_fclose (&mask_fp);

                  return -1;
                }
              }

              hcfree (line_buf);

              hc_fclose (&mask_fp);
            }
            else
            {
              event_log_error (hashcat_ctx, "%s: unsupported file type.", arg);

              return -1;
            }
          }
        }
      }
      else
      {
        const char *mask = DEF_MASK;

        if (mask_append (hashcat_ctx, mask, NULL) == -1) return -1;
      }
    }
    else
    {
      const char *mask = hashconfig->benchmark_mask;

      if (mask_append (hashcat_ctx, mask, NULL) == -1) return -1;
    }
  }
  else if (user_options->attack_mode == ATTACK_MODE_HYBRID1)
  {
    // display

    char *arg = user_options_extra->hc_workv[user_options_extra->hc_workc - 1];

    // mod

    if (hc_path_exist (arg) == false)
    {
      if (mask_append (hashcat_ctx, arg, NULL) == -1) return -1;
    }
    else
    {
      if (hc_path_is_file (arg) == true)
      {
        mask_ctx->mask_from_file = true;

        HCFILE mask_fp;

        if (hc_fopen (&mask_fp, arg, "r") == false)
        {
          event_log_error (hashcat_ctx, "%s: %s", arg, strerror (errno));

          return -1;
        }

        char *line_buf = (char *) hcmalloc (HCBUFSIZ_LARGE);

        while (!hc_feof (&mask_fp))
        {
          const size_t line_len = fgetl (&mask_fp, line_buf, HCBUFSIZ_LARGE);

          if (line_len == 0) continue;

          if (line_buf[0] == '#') continue;

          char *mask_buf = mask_ctx_parse_maskfile_find_mask (line_buf, line_len);

          char *prepend_buf = NULL;

          if (line_buf != mask_buf)
          {
            // if we have custom charsets

            prepend_buf = line_buf;

            mask_buf[-1] = 0;
          }

          if (mask_append (hashcat_ctx, mask_buf, prepend_buf) == -1)
          {
            hc_fclose (&mask_fp);

            return -1;
          }
        }

        hcfree (line_buf);

        hc_fclose (&mask_fp);
      }
      else
      {
        event_log_error (hashcat_ctx, "%s: unsupported file type.", arg);

        return -1;
      }
    }
  }
  else if (user_options->attack_mode == ATTACK_MODE_HYBRID2)
  {
    // display

    char *arg = user_options_extra->hc_workv[0];

    // mod

    if (hc_path_exist (arg) == false)
    {
      if (mask_append (hashcat_ctx, arg, NULL) == -1) return -1;
    }
    else
    {
      if (hc_path_is_file (arg) == true)
      {
        mask_ctx->mask_from_file = true;

        HCFILE mask_fp;

        if (hc_fopen (&mask_fp, arg, "r") == false)
        {
          event_log_error (hashcat_ctx, "%s: %s", arg, strerror (errno));

          return -1;
        }

        char *line_buf = (char *) hcmalloc (HCBUFSIZ_LARGE);

        while (!hc_feof (&mask_fp))
        {
          const size_t line_len = fgetl (&mask_fp, line_buf, HCBUFSIZ_LARGE);

          if (line_len == 0) continue;

          if (line_buf[0] == '#') continue;

          char *mask_buf = mask_ctx_parse_maskfile_find_mask (line_buf, line_len);

          char *prepend_buf = NULL;

          if (line_buf != mask_buf)
          {
            // if we have custom charsets

            prepend_buf = line_buf;

            mask_buf[-1] = 0;
          }

          if (mask_append (hashcat_ctx, mask_buf, prepend_buf) == -1)
          {
            hc_fclose (&mask_fp);

            return -1;
          }
        }

        hcfree (line_buf);

        hc_fclose (&mask_fp);
      }
      else
      {
        event_log_error (hashcat_ctx, "%s: unsupported file type.", arg);

        return -1;
      }
    }
  }

  if (mask_ctx->masks_cnt == 0)
  {
    event_log_error (hashcat_ctx, "Invalid mask.");

    return -1;
  }

  mask_ctx->mask = mask_ctx->masks[0];

  return 0;
}