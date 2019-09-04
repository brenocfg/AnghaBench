#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int slow_candidates; } ;
typedef  TYPE_2__ user_options_t ;
typedef  int u32 ;
struct TYPE_9__ {int css_cnt; TYPE_1__* css_buf; } ;
typedef  TYPE_3__ mask_ctx_t ;
struct TYPE_10__ {scalar_t__ attack_exec; int opts_type; } ;
typedef  TYPE_4__ hashconfig_t ;
struct TYPE_11__ {TYPE_2__* user_options; TYPE_4__* hashconfig; TYPE_3__* mask_ctx; } ;
typedef  TYPE_5__ hashcat_ctx_t ;
struct TYPE_7__ {int cs_len; } ;

/* Variables and functions */
 scalar_t__ ATTACK_EXEC_INSIDE_KERNEL ; 
 int OPTS_TYPE_PT_UTF16BE ; 
 int OPTS_TYPE_PT_UTF16LE ; 

__attribute__((used)) static void mp_css_split_cnt (hashcat_ctx_t *hashcat_ctx, const u32 css_cnt_orig, u32 css_cnt_lr[2])
{
  const mask_ctx_t     *mask_ctx     = hashcat_ctx->mask_ctx;
  const hashconfig_t   *hashconfig   = hashcat_ctx->hashconfig;
  const user_options_t *user_options = hashcat_ctx->user_options;

  u32 css_cnt_l = mask_ctx->css_cnt;
  u32 css_cnt_r;

  if (user_options->slow_candidates == true)
  {
    css_cnt_r = 0;
  }
  else
  {
    if (hashconfig->attack_exec == ATTACK_EXEC_INSIDE_KERNEL)
    {
      if (css_cnt_orig < 6)
      {
        css_cnt_r = 1;
      }
      else if (css_cnt_orig == 6)
      {
        css_cnt_r = 2;
      }
      else
      {
        if ((hashconfig->opts_type & OPTS_TYPE_PT_UTF16LE) || (hashconfig->opts_type & OPTS_TYPE_PT_UTF16BE))
        {
          if (css_cnt_orig == 8 || css_cnt_orig == 10)
          {
            css_cnt_r = 2;
          }
          else
          {
            css_cnt_r = 4;
          }
        }
        else
        {
          if ((mask_ctx->css_buf[0].cs_len * mask_ctx->css_buf[1].cs_len * mask_ctx->css_buf[2].cs_len) > 256)
          {
            css_cnt_r = 3;
          }
          else
          {
            css_cnt_r = 4;
          }
        }
      }
    }
    else
    {
      css_cnt_r = 1;

      /* unfinished code?
      int sum = css_buf[css_cnt_r - 1].cs_len;

      for (u32 i = 1; i < 4 && i < css_cnt; i++)
      {
        if (sum > 1) break; // we really don't need alot of amplifier them for slow hashes

        css_cnt_r++;

        sum *= css_buf[css_cnt_r - 1].cs_len;
      }
      */
    }
  }

  css_cnt_l -= css_cnt_r;

  css_cnt_lr[0] = css_cnt_l;
  css_cnt_lr[1] = css_cnt_r;
}