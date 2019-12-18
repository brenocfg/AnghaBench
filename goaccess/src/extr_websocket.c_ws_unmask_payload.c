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

__attribute__((used)) static void
ws_unmask_payload (char *buf, int len, int offset, unsigned char mask[])
{
  int i, j = 0;

  /* unmask data */
  for (i = offset; i < len; ++i, ++j) {
    buf[i] ^= mask[j % 4];
  }
}