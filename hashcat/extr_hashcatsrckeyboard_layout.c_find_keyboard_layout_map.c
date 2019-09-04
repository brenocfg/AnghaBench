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
typedef  int u32 ;
struct TYPE_3__ {int src_char; int src_len; } ;
typedef  TYPE_1__ keyboard_layout_mapping_t ;

/* Variables and functions */

int find_keyboard_layout_map (const u32 search, const int search_len, const keyboard_layout_mapping_t *s_keyboard_layout_mapping, const int keyboard_layout_mapping_cnt)
{
  for (int idx = 0; idx < keyboard_layout_mapping_cnt; idx++)
  {
    const u32 src_char = s_keyboard_layout_mapping[idx].src_char;
    const int src_len  = s_keyboard_layout_mapping[idx].src_len;

    if (src_len == search_len)
    {
      const u32 mask = 0xffffffff >> ((4 - search_len) * 8);

      if ((src_char & mask) == (search & mask)) return idx;
    }
  }

  return -1;
}