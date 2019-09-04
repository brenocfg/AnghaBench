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
 size_t const PW_MAX ; 
 int /*<<< orphan*/  u8_to_hex (scalar_t__ const,scalar_t__*) ; 

void exec_hexify (const u8 *buf, const size_t len, u8 *out)
{
  const size_t max_len = (len > PW_MAX) ? PW_MAX : len;

  for (int i = (int) max_len - 1, j = i * 2; i >= 0; i -= 1, j -= 2)
  {
    u8_to_hex (buf[i], out + j);
  }

  out[max_len * 2] = 0;
}