#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_4__ {int dst_char; int dst_len; } ;
typedef  TYPE_1__ keyboard_layout_mapping_t ;

/* Variables and functions */
 int MIN (int const,int) ; 
 int find_keyboard_layout_map (int const,int,TYPE_1__ const*,int const) ; 

int execute_keyboard_layout_mapping (u32 plain_buf[64], const int plain_len, const keyboard_layout_mapping_t *s_keyboard_layout_mapping, const int keyboard_layout_mapping_cnt)
{
  u32 out_buf[16] = { 0 };

  u8 *out_ptr = (u8 *) out_buf;

  int out_len = 0;

  u8 *plain_ptr = (u8 *) plain_buf;

  int plain_pos = 0;

  while (plain_pos < plain_len)
  {
    u32 src0 = 0;
    u32 src1 = 0;
    u32 src2 = 0;
    u32 src3 = 0;

    const int rem = MIN (plain_len - plain_pos, 4);

    if (rem > 0) src0 = plain_ptr[plain_pos + 0];
    if (rem > 1) src1 = plain_ptr[plain_pos + 1];
    if (rem > 2) src2 = plain_ptr[plain_pos + 2];
    if (rem > 3) src3 = plain_ptr[plain_pos + 3];

    const u32 src = (src0 <<  0)
                  | (src1 <<  8)
                  | (src2 << 16)
                  | (src3 << 24);

    int src_len;

    for (src_len = rem; src_len > 0; src_len--)
    {
      const int idx = find_keyboard_layout_map (src, src_len, s_keyboard_layout_mapping, keyboard_layout_mapping_cnt);

      if (idx == -1) continue;

      u32 dst_char = s_keyboard_layout_mapping[idx].dst_char;
      int dst_len  = s_keyboard_layout_mapping[idx].dst_len;

      switch (dst_len)
      {
        case 1:
          out_ptr[out_len++] = (dst_char >>  0) & 0xff;
          break;
        case 2:
          out_ptr[out_len++] = (dst_char >>  0) & 0xff;
          out_ptr[out_len++] = (dst_char >>  8) & 0xff;
          break;
        case 3:
          out_ptr[out_len++] = (dst_char >>  0) & 0xff;
          out_ptr[out_len++] = (dst_char >>  8) & 0xff;
          out_ptr[out_len++] = (dst_char >> 16) & 0xff;
          break;
        case 4:
          out_ptr[out_len++] = (dst_char >>  0) & 0xff;
          out_ptr[out_len++] = (dst_char >>  8) & 0xff;
          out_ptr[out_len++] = (dst_char >> 16) & 0xff;
          out_ptr[out_len++] = (dst_char >> 24) & 0xff;
          break;
      }

      plain_pos += src_len;

      break;
    }

    // not matched, keep original

    if (src_len == 0)
    {
      out_ptr[out_len] = plain_ptr[plain_pos];

      out_len++;

      plain_pos++;
    }
  }

  plain_buf[ 0] = out_buf[ 0];
  plain_buf[ 1] = out_buf[ 1];
  plain_buf[ 2] = out_buf[ 2];
  plain_buf[ 3] = out_buf[ 3];
  plain_buf[ 4] = out_buf[ 4];
  plain_buf[ 5] = out_buf[ 5];
  plain_buf[ 6] = out_buf[ 6];
  plain_buf[ 7] = out_buf[ 7];
  plain_buf[ 8] = out_buf[ 8];
  plain_buf[ 9] = out_buf[ 9];
  plain_buf[10] = out_buf[10];
  plain_buf[11] = out_buf[11];
  plain_buf[12] = out_buf[12];
  plain_buf[13] = out_buf[13];
  plain_buf[14] = out_buf[14];
  plain_buf[15] = out_buf[15];

  return out_len;
}