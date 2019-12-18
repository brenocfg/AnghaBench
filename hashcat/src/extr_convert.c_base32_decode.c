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
typedef  int u8 ;

/* Variables and functions */

size_t base32_decode (u8 (*f) (const u8), const u8 *in_buf, const size_t in_len, u8 *out_buf)
{
  const u8 *in_ptr = in_buf;

  u8 *out_ptr = out_buf;

  for (size_t i = 0; i < in_len; i += 8)
  {
    const u8 f0 = ((i + 0) < in_len) ? in_ptr[0] : 0;
    const u8 f1 = ((i + 1) < in_len) ? in_ptr[1] : 0;
    const u8 f2 = ((i + 2) < in_len) ? in_ptr[2] : 0;
    const u8 f3 = ((i + 3) < in_len) ? in_ptr[3] : 0;
    const u8 f4 = ((i + 4) < in_len) ? in_ptr[4] : 0;
    const u8 f5 = ((i + 5) < in_len) ? in_ptr[5] : 0;
    const u8 f6 = ((i + 6) < in_len) ? in_ptr[6] : 0;
    const u8 f7 = ((i + 7) < in_len) ? in_ptr[7] : 0;

    const u8 out_val0 = f (f0 & 0x7f);
    const u8 out_val1 = f (f1 & 0x7f);
    const u8 out_val2 = f (f2 & 0x7f);
    const u8 out_val3 = f (f3 & 0x7f);
    const u8 out_val4 = f (f4 & 0x7f);
    const u8 out_val5 = f (f5 & 0x7f);
    const u8 out_val6 = f (f6 & 0x7f);
    const u8 out_val7 = f (f7 & 0x7f);

    out_ptr[0] =                            ((out_val0 << 3) & 0xf8) | ((out_val1 >> 2) & 0x07);
    out_ptr[1] = ((out_val1 << 6) & 0xc0) | ((out_val2 << 1) & 0x3e) | ((out_val3 >> 4) & 0x01);
    out_ptr[2] =                            ((out_val3 << 4) & 0xf0) | ((out_val4 >> 1) & 0x0f);
    out_ptr[3] = ((out_val4 << 7) & 0x80) | ((out_val5 << 2) & 0x7c) | ((out_val6 >> 3) & 0x03);
    out_ptr[4] =                            ((out_val6 << 5) & 0xe0) | ((out_val7 >> 0) & 0x1f);

    in_ptr  += 8;
    out_ptr += 5;
  }

  size_t tmp_len = 0;

  for (size_t i = 0; i < in_len; i++, tmp_len++)
  {
    if (in_buf[i] != '=') continue;

    break;
  }

  size_t out_len = (tmp_len * 5) / 8;

  return out_len;
}