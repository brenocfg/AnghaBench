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
 int caution ; 
 scalar_t__ gdb_has_a_terminal () ; 
 scalar_t__ instream ; 
 scalar_t__ stdin ; 

int
input_from_terminal_p (void)
{
  return gdb_has_a_terminal () && (instream == stdin) & caution;
}