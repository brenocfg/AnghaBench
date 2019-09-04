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
typedef  int limb ;

/* Variables and functions */

__attribute__((used)) static void fscalar_product(limb *output, const limb *in, const limb scalar) {
  unsigned i;
  for (i = 0; i < 10; ++i) {
    output[i] = in[i] * scalar;
  }
}