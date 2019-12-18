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
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  ui_file_write (int /*<<< orphan*/ ,char*,int) ; 

int
putchar_unfiltered (int c)
{
  char buf = c;
  ui_file_write (gdb_stdout, &buf, 1);
  return c;
}