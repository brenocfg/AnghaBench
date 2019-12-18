#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  size_t u32 ;
struct TYPE_3__ {int cs_len; } ;
typedef  TYPE_1__ cs_t ;

/* Variables and functions */
 int overflow_check_u64_mul (int,int) ; 

__attribute__((used)) static int sp_get_sum (u32 start, u32 stop, cs_t *root_css_buf, u64 *result)
{
  u64 sum = 1;

  u32 i;

  for (i = start; i < stop; i++)
  {
    if (overflow_check_u64_mul (sum, root_css_buf[i].cs_len) == false) return -1;

    sum *= root_css_buf[i].cs_len;
  }

  *result = sum;

  return 0;
}