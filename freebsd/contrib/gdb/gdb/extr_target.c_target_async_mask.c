#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int target_async_mask_value ; 

int
target_async_mask (int mask)
{
  int saved_async_masked_status = target_async_mask_value;
  target_async_mask_value = mask;
  return saved_async_masked_status;
}