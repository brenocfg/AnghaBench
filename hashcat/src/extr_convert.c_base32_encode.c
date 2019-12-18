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

size_t base32_encode (u8 (*f) (const u8), const u8 *in_buf, const size_t in_len, u8 *out_buf)
{
  const u8 *in_ptr = in_buf;

  u8 *out_ptr = out_buf;

  for (size_t i = 0; i < in_len; i += 5)
  {
    const u8 f0 = ((i + 0) < in_len) ? in_ptr[0] : 0;
    const u8 f1 = ((i + 1) < in_len) ? in_ptr[1] : 0;
    const u8 f2 = ((i + 2) < in_len) ? in_ptr[2] : 0;
    const u8 f3 = ((i + 3) < in_len) ? in_ptr[3] : 0;
    const u8 f4 = ((i + 4) < in_len) ? in_ptr[4] : 0;

    const u8 out_val0 = f (                     ((f0 >> 3) & 0x1f));
    const u8 out_val1 = f (((f0 << 2) & 0x1c) | ((f1 >> 6) & 0x03));
    const u8 out_val2 = f (                     ((f1 >> 1) & 0x1f));
    const u8 out_val3 = f (((f1 << 4) & 0x10) | ((f2 >> 4) & 0x0f));
    const u8 out_val4 = f (((f2 << 1) & 0x1e) | ((f3 >> 7) & 0x01));
    const u8 out_val5 = f (                     ((f3 >> 2) & 0x1f));
    const u8 out_val6 = f (((f3 << 3) & 0x18) | ((f4 >> 5) & 0x07));
    const u8 out_val7 = f (                     ((f4 >> 0) & 0x1f));

    out_ptr[0] = out_val0 & 0x7f;
    out_ptr[1] = out_val1 & 0x7f;
    out_ptr[2] = out_val2 & 0x7f;
    out_ptr[3] = out_val3 & 0x7f;
    out_ptr[4] = out_val4 & 0x7f;
    out_ptr[5] = out_val5 & 0x7f;
    out_ptr[6] = out_val6 & 0x7f;
    out_ptr[7] = out_val7 & 0x7f;

    in_ptr  += 5;
    out_ptr += 8;
  }

  int out_len = (int) (((0.5 + in_len) * 8) / 5); // ceil (in_len * 8 / 5)

  while (out_len % 8)
  {
    out_buf[out_len] = '=';

    out_len++;
  }

  return out_len;
}