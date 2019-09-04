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
 int /*<<< orphan*/  squeeze (unsigned int*) ; 

__attribute__((used)) static void square(unsigned int out[32],const unsigned int a[32])
{
  unsigned int i;
  unsigned int j;
  unsigned int u;

  for (i = 0;i < 32;++i) {
    u = 0;
    for (j = 0;j < i - j;++j) u += a[j] * a[i - j];
    for (j = i + 1;j < i + 32 - j;++j) u += 38 * a[j] * a[i + 32 - j];
    u *= 2;
    if ((i & 1) == 0) {
      u += a[i / 2] * a[i / 2];
      u += 38 * a[i / 2 + 16] * a[i / 2 + 16];
    }
    out[i] = u;
  }
  squeeze(out);
}