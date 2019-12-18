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
struct symtab {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_source_lines_base (struct symtab*,int,int,int) ; 

void
print_source_lines (struct symtab *s, int line, int stopline, int noerror)
{
  print_source_lines_base (s, line, stopline, noerror);
}