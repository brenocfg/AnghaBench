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
typedef  int /*<<< orphan*/  value_t ;

/* Variables and functions */
 int* VALUE_INTS ; 

__attribute__((used)) static inline void store_value_rev (int **P, value_t value) {
  //*(--(*(value_t **)P)) = value;
  //GNU C MUST DIE
  int *PVal = (*P) - VALUE_INTS;
  *(value_t *)PVal = value;
  *P = PVal;
}