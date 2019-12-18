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
struct ui_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,unsigned long) ; 

void
gdb_print_host_address (const void *addr, struct ui_file *stream)
{

  /* We could use the %p conversion specifier to fprintf if we had any
     way of knowing whether this host supports it.  But the following
     should work on the Alpha and on 32 bit machines.  */

  fprintf_filtered (stream, "0x%lx", (unsigned long) addr);
}