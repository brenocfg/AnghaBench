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
typedef  scalar_t__ ecma_char_t ;

/* Variables and functions */

__attribute__((used)) static bool
search_char_in_char_array (ecma_char_t c,               /**< code unit */
                           const ecma_char_t *array,    /**< array */
                           int size_of_array)           /**< length of the array */
{
  int bottom = 0;
  int top = size_of_array - 1;

  while (bottom <= top)
  {
    int middle = (bottom + top) / 2;
    ecma_char_t current = array[middle];

    if (current == c)
    {
      return true;
    }

    if (c < current)
    {
      top = middle - 1;
    }
    else
    {
      bottom = middle + 1;
    }
  }

  return false;
}