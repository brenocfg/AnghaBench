#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_4__ {int cnt; int len; int off; } ;
typedef  TYPE_1__ pw_idx_t ;
struct TYPE_5__ {scalar_t__ pws_cnt; scalar_t__ kernel_power; int pws_comp; TYPE_1__* pws_idx; } ;
typedef  TYPE_2__ hc_device_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int const) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  stderr ; 

void pw_add (hc_device_param_t *device_param, const u8 *pw_buf, const int pw_len)
{
  if (device_param->pws_cnt < device_param->kernel_power)
  {
    pw_idx_t *pw_idx = device_param->pws_idx + device_param->pws_cnt;

    const u32 pw_len4 = (pw_len + 3) & ~3; // round up to multiple of 4

    const u32 pw_len4_cnt = pw_len4 / 4;

    pw_idx->cnt = pw_len4_cnt;
    pw_idx->len = pw_len;

    u8 *dst = (u8 *) (device_param->pws_comp + pw_idx->off);

    memcpy (dst, pw_buf, pw_len);

    memset (dst + pw_len, 0, pw_len4 - pw_len);

    // prepare next element

    pw_idx_t *pw_idx_next = pw_idx + 1;

    pw_idx_next->off = pw_idx->off + pw_idx->cnt;

    device_param->pws_cnt++;
  }
  else
  {
    fprintf (stderr, "BUG pw_add()!!\n");

    return;
  }
}