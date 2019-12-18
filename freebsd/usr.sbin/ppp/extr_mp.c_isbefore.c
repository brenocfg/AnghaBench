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
typedef  scalar_t__ u_int32_t ;

/* Variables and functions */

__attribute__((used)) static int
isbefore(unsigned is12bit, u_int32_t seq1, u_int32_t seq2)
{
  u_int32_t max = (is12bit ? 0xfff : 0xffffff) - 0x200;

  if (seq1 > max) {
    if (seq2 < 0x200 || seq2 > seq1)
      return 1;
  } else if ((seq1 > 0x200 || seq2 <= max) && seq1 < seq2)
    return 1;

  return 0;
}