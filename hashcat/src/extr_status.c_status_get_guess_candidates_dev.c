#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ attack_kern; } ;
typedef  TYPE_1__ user_options_extra_t ;
typedef  char u8 ;
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_13__ {int accessible; } ;
typedef  TYPE_2__ status_ctx_t ;
struct TYPE_14__ {scalar_t__ const member_0; scalar_t__ const member_1; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; } ;
typedef  TYPE_3__ plain_t ;
struct TYPE_15__ {int skipped; int skipped_warning; scalar_t__ outerloop_left; scalar_t__ innerloop_left; } ;
typedef  TYPE_4__ hc_device_param_t ;
struct TYPE_16__ {int opts_type; } ;
typedef  TYPE_5__ hashconfig_t ;
struct TYPE_17__ {TYPE_1__* user_options_extra; TYPE_2__* status_ctx; TYPE_7__* backend_ctx; TYPE_5__* hashconfig; } ;
typedef  TYPE_6__ hashcat_ctx_t ;
struct TYPE_18__ {TYPE_4__* devices_param; } ;
typedef  TYPE_7__ backend_ctx_t ;

/* Variables and functions */
 scalar_t__ ATTACK_KERN_BF ; 
 int /*<<< orphan*/  HCBUFSIZ_TINY ; 
 int OPTS_TYPE_PT_ALWAYS_ASCII ; 
 int /*<<< orphan*/  build_plain (TYPE_6__*,TYPE_4__*,TYPE_3__*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  exec_hexify (char*,int,char*) ; 
 scalar_t__ hcmalloc (int /*<<< orphan*/ ) ; 
 int need_hexify (char*,int,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 

char *status_get_guess_candidates_dev (const hashcat_ctx_t *hashcat_ctx, const int backend_devices_idx)
{
  const hashconfig_t         *hashconfig         = hashcat_ctx->hashconfig;
  const backend_ctx_t        *backend_ctx        = hashcat_ctx->backend_ctx;
  const status_ctx_t         *status_ctx         = hashcat_ctx->status_ctx;
  const user_options_extra_t *user_options_extra = hashcat_ctx->user_options_extra;

  if (status_ctx->accessible == false) return NULL;

  hc_device_param_t *device_param = &backend_ctx->devices_param[backend_devices_idx];

  char *display = (char *) hcmalloc (HCBUFSIZ_TINY);

  if ((device_param->skipped == true) || (device_param->skipped_warning == true))
  {
    snprintf (display, HCBUFSIZ_TINY, "[Skipped]");

    return display;
  }

  if (user_options_extra->attack_kern == ATTACK_KERN_BF)
  {
    snprintf (display, HCBUFSIZ_TINY, "[Generating]");
  }
  else
  {
    snprintf (display, HCBUFSIZ_TINY, "[Copying]");
  }

  if ((device_param->outerloop_left == 0) || (device_param->innerloop_left == 0)) return display;

  const u64 outerloop_first = 0;
  const u64 outerloop_last  = device_param->outerloop_left - 1;

  const u32 innerloop_first = 0;
  const u32 innerloop_last  = device_param->innerloop_left - 1;

  plain_t plain1 = { outerloop_first, innerloop_first, 0, 0, 0, 0, 0 };
  plain_t plain2 = { outerloop_last,  innerloop_last,  0, 0, 0, 0, 0 };

  u32 plain_buf1[(64 * 2) + 2] = { 0 };
  u32 plain_buf2[(64 * 2) + 2] = { 0 };

  u8 *plain_ptr1 = (u8 *) plain_buf1;
  u8 *plain_ptr2 = (u8 *) plain_buf2;

  int plain_len1 = 0;
  int plain_len2 = 0;

  build_plain ((hashcat_ctx_t *) hashcat_ctx, device_param, &plain1, plain_buf1, &plain_len1);
  build_plain ((hashcat_ctx_t *) hashcat_ctx, device_param, &plain2, plain_buf2, &plain_len2);

  const bool always_ascii = (hashconfig->opts_type & OPTS_TYPE_PT_ALWAYS_ASCII) ? true : false;

  const bool need_hex1 = need_hexify (plain_ptr1, plain_len1, 0, always_ascii);
  const bool need_hex2 = need_hexify (plain_ptr2, plain_len2, 0, always_ascii);

  if ((need_hex1 == true) || (need_hex2 == true))
  {
    exec_hexify (plain_ptr1, plain_len1, plain_ptr1);
    exec_hexify (plain_ptr2, plain_len2, plain_ptr2);

    plain_ptr1[plain_len1 * 2] = 0;
    plain_ptr2[plain_len2 * 2] = 0;

    snprintf (display, HCBUFSIZ_TINY, "$HEX[%s] -> $HEX[%s]", plain_ptr1, plain_ptr2);
  }
  else
  {
    plain_ptr1[plain_len1] = 0;
    plain_ptr2[plain_len2] = 0;

    snprintf (display, HCBUFSIZ_TINY, "%s -> %s", plain_ptr1, plain_ptr2);
  }

  return display;
}