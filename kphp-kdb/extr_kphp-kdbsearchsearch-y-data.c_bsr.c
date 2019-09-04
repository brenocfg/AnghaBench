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

__attribute__((used)) static int bsr (int i) {
  int r, t;
  asm("bsr %1,%0\n\t"
    : "=&q" (r), "=&q" (t)
    : "1" (i)
    : "cc");
  return r;
}