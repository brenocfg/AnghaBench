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
typedef  double ecma_number_t ;

/* Variables and functions */
 int rand () ; 

__attribute__((used)) static ecma_number_t
generate_number (void)
{
  ecma_number_t num = ((ecma_number_t) rand () / 32767.0);
  if (rand () % 2)
  {
    num = -num;
  }
  int power = rand () % 30;
  while (power-- > 0)
  {
    num *= 10;
  }
  return num;
}