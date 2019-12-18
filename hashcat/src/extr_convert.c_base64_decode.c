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

size_t base64_decode (u8 (*f) (const u8), const u8 *in_buf, const size_t in_len, u8 *out_buf)
{
  const u8 *in_ptr = in_buf;

  u8 *out_ptr = out_buf;

  for (size_t i = 0; i < in_len; i += 4)
  {
    const u8 f0 = ((i + 0) < in_len) ? in_ptr[0] : 0;
    const u8 f1 = ((i + 1) < in_len) ? in_ptr[1] : 0;
    const u8 f2 = ((i + 2) < in_len) ? in_ptr[2] : 0;
    const u8 f3 = ((i + 3) < in_len) ? in_ptr[3] : 0;

    const u8 out_val0 = f (f0 & 0x7f);
    const u8 out_val1 = f (f1 & 0x7f);
    const u8 out_val2 = f (f2 & 0x7f);
    const u8 out_val3 = f (f3 & 0x7f);

    out_ptr[0] = ((out_val0 << 2) & 0xfc) | ((out_val1 >> 4) & 0x03);
    out_ptr[1] = ((out_val1 << 4) & 0xf0) | ((out_val2 >> 2) & 0x0f);
    out_ptr[2] = ((out_val2 << 6) & 0xc0) | ((out_val3 >> 0) & 0x3f);

    in_ptr  += 4;
    out_ptr += 3;
  }

  size_t tmp_len = 0;

  for (size_t i = 0; i < in_len; i++, tmp_len++)
  {
    if (in_buf[i] != '=') continue;

    break;
  }

  size_t out_len = (tmp_len * 6) / 8;

  return out_len;
}