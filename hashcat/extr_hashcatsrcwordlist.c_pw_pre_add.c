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
struct TYPE_4__ {int pw_len; int base_len; int rule_idx; int /*<<< orphan*/  base_buf; int /*<<< orphan*/  pw_buf; } ;
typedef  TYPE_1__ pw_pre_t ;
struct TYPE_5__ {scalar_t__ pws_pre_cnt; scalar_t__ kernel_power; TYPE_1__* pws_pre_buf; } ;
typedef  TYPE_2__ hc_device_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int const) ; 
 int /*<<< orphan*/  stdout ; 

void pw_pre_add (hc_device_param_t *device_param, const u8 *pw_buf, const int pw_len, const u8 *base_buf, const int base_len, const int rule_idx)
{
  if (device_param->pws_pre_cnt < device_param->kernel_power)
  {
    pw_pre_t *pw_pre = device_param->pws_pre_buf + device_param->pws_pre_cnt;

    memcpy (pw_pre->pw_buf, pw_buf, pw_len);

    pw_pre->pw_len = pw_len;

    if (base_buf != NULL)
    {
      memcpy (pw_pre->base_buf, base_buf, base_len);

      pw_pre->base_len = base_len;
    }

    pw_pre->rule_idx = rule_idx;

    device_param->pws_pre_cnt++;
  }
  else
  {
    fprintf (stdout, "BUG pw_pre_add()!!\n");

    return;
  }
}