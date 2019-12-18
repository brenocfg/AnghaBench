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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  vfprintf_maybe_filtered (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int) ; 

void
vprintf_filtered (const char *format, va_list args)
{
  vfprintf_maybe_filtered (gdb_stdout, format, args, 1);
}