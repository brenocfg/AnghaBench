#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int css_cnt; TYPE_3__* css_buf; } ;
typedef  TYPE_1__ mask_ctx_t ;
struct TYPE_9__ {TYPE_1__* mask_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
struct TYPE_10__ {int cs_len; scalar_t__* cs_buf; } ;
typedef  TYPE_3__ cs_t ;

/* Variables and functions */
 scalar_t__ hccalloc (int,int) ; 
 int /*<<< orphan*/  hcfree (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 

__attribute__((used)) static int mp_css_utf16le_expand (hashcat_ctx_t *hashcat_ctx)
{
  mask_ctx_t *mask_ctx = hashcat_ctx->mask_ctx;

  u32 css_cnt_utf16le = mask_ctx->css_cnt * 2;

  if (css_cnt_utf16le > 256) return -1;

  cs_t *css_buf_utf16le = (cs_t *) hccalloc (css_cnt_utf16le, sizeof (cs_t));

  for (u32 i = 0, j = 0; i < mask_ctx->css_cnt; i += 1, j += 2)
  {
    memcpy (&css_buf_utf16le[j + 0], &mask_ctx->css_buf[i], sizeof (cs_t));

    css_buf_utf16le[j + 1].cs_buf[0] = 0;
    css_buf_utf16le[j + 1].cs_len    = 1;
  }

  memcpy (mask_ctx->css_buf, css_buf_utf16le, css_cnt_utf16le * sizeof (cs_t));

  mask_ctx->css_cnt = css_cnt_utf16le;

  hcfree (css_buf_utf16le);

  return 0;
}