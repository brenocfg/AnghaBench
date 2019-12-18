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
 int /*<<< orphan*/  hex_to_u8 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t const) ; 

size_t exec_unhexify (const u8 *in_buf, const size_t in_len, u8 *out_buf, const size_t out_sz)
{
  size_t i, j;

  for (i = 0, j = 5; j < in_len - 1; i += 1, j += 2)
  {
    const u8 c = hex_to_u8 (&in_buf[j]);

    out_buf[i] = c;
  }

  memset (out_buf + i, 0, out_sz - i);

  return (i);
}