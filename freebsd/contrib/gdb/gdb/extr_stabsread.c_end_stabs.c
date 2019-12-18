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
 scalar_t__ previous_stab_code ; 
 scalar_t__ type_vector ; 
 scalar_t__ type_vector_length ; 
 int /*<<< orphan*/  xfree (scalar_t__) ; 

void
end_stabs (void)
{
  if (type_vector)
    {
      xfree (type_vector);
    }
  type_vector = 0;
  type_vector_length = 0;
  previous_stab_code = 0;
}