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

__attribute__((used)) static int unpack_extra_mask (int extra_mask) {
  int res = extra_mask & 0xff;
  res += 3*(extra_mask & 0x100);
  res += 6*(extra_mask & 0x200);
  res += 12*(extra_mask & 0x400);
  res += 24*(extra_mask & 0x800);
  return res;
}