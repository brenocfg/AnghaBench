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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ const RULE_LAST_REJECTED_SAVED_POS ; 
 int conv_ctoi (scalar_t__ const) ; 

__attribute__((used)) static int conv_pos (const u8 c, const int pos_mem)
{
  if (c == RULE_LAST_REJECTED_SAVED_POS)
  {
    return pos_mem;
  }

  return conv_ctoi (c);
}