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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  u8_to_hex (int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 

int hex_encode (const u8 *in_buf, const int in_len, u8 *out_buf)
{
  for (int i = 0, j = 0; i < in_len; i += 1, j += 2)
  {
    u8_to_hex (in_buf[i], &out_buf[j]);
  }

  return in_len * 2;
}