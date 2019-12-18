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
 int /*<<< orphan*/  fputstr_filtered (char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  puts_filtered (char*) ; 

__attribute__((used)) static void
print_packet (char *buf)
{
  puts_filtered ("\"");
  fputstr_filtered (buf, '"', gdb_stdout);
  puts_filtered ("\"");
}