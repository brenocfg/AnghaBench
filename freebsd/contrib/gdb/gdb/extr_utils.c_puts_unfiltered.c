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
 int /*<<< orphan*/  fputs_unfiltered (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 

void
puts_unfiltered (const char *string)
{
  fputs_unfiltered (string, gdb_stdout);
}