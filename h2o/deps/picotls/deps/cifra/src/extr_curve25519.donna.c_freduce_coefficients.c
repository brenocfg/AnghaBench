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
 int div_by_2_25 (int) ; 
 int div_by_2_26 (int) ; 

__attribute__((used)) static void freduce_coefficients(limb *output) {
  unsigned i;

  output[10] = 0;

  for (i = 0; i < 10; i += 2) {
    limb over = div_by_2_26(output[i]);
    /* The entry condition (that |output[i]| < 280*2^54) means that over is, at
     * most, 280*2^28 in the first iteration of this loop. This is added to the
     * next limb and we can approximate the resulting bound of that limb by
     * 281*2^54. */
    output[i] -= over << 26;
    output[i+1] += over;

    /* For the first iteration, |output[i+1]| < 281*2^54, thus |over| <
     * 281*2^29. When this is added to the next limb, the resulting bound can
     * be approximated as 281*2^54.
     *
     * For subsequent iterations of the loop, 281*2^54 remains a conservative
     * bound and no overflow occurs. */
    over = div_by_2_25(output[i+1]);
    output[i+1] -= over << 25;
    output[i+2] += over;
  }
  /* Now |output[10]| < 281*2^29 and all other coefficients are reduced. */
  output[0] += output[10] << 4;
  output[0] += output[10] << 1;
  output[0] += output[10];

  output[10] = 0;

  /* Now output[1..9] are reduced, and |output[0]| < 2^26 + 19*281*2^29
   * So |over| will be no more than 2^16. */
  {
    limb over = div_by_2_26(output[0]);
    output[0] -= over << 26;
    output[1] += over;
  }

  /* Now output[0,2..9] are reduced, and |output[1]| < 2^25 + 2^16 < 2^26. The
   * bound on |output[1]| is sufficient to meet our needs. */
}