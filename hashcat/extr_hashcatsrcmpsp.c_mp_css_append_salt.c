#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct TYPE_10__ {size_t salt_len; scalar_t__ salt_buf; } ;
typedef  TYPE_1__ salt_t ;
struct TYPE_11__ {int css_cnt; TYPE_4__* css_buf; } ;
typedef  TYPE_2__ mask_ctx_t ;
struct TYPE_12__ {TYPE_2__* mask_ctx; } ;
typedef  TYPE_3__ hashcat_ctx_t ;
struct TYPE_13__ {int cs_len; int /*<<< orphan*/ * cs_buf; } ;
typedef  TYPE_4__ cs_t ;

/* Variables and functions */
 scalar_t__ hccalloc (size_t,int) ; 
 int /*<<< orphan*/  hcfree (TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_4__*,int) ; 

__attribute__((used)) static int mp_css_append_salt (hashcat_ctx_t *hashcat_ctx, salt_t *salt_buf)
{
  mask_ctx_t *mask_ctx = hashcat_ctx->mask_ctx;

  u32  salt_len     =        salt_buf->salt_len;
  u8  *salt_buf_ptr = (u8 *) salt_buf->salt_buf;

  u32 css_cnt_salt = mask_ctx->css_cnt + salt_len;

  cs_t *css_buf_salt = (cs_t *) hccalloc (css_cnt_salt, sizeof (cs_t));

  memcpy (css_buf_salt, mask_ctx->css_buf, mask_ctx->css_cnt * sizeof (cs_t));

  for (u32 i = 0, j = mask_ctx->css_cnt; i < salt_len; i++, j++)
  {
    css_buf_salt[j].cs_buf[0] = salt_buf_ptr[i];
    css_buf_salt[j].cs_len    = 1;
  }

  hcfree (mask_ctx->css_buf);

  mask_ctx->css_buf = css_buf_salt;
  mask_ctx->css_cnt = css_cnt_salt;

  return 0;
}