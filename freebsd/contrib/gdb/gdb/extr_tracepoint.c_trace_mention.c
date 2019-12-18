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
struct tracepoint {int /*<<< orphan*/  line_number; int /*<<< orphan*/ * source_file; int /*<<< orphan*/  address; int /*<<< orphan*/  number; } ;

/* Variables and functions */
 scalar_t__ addressprint ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  print_address_numeric (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 

__attribute__((used)) static void
trace_mention (struct tracepoint *tp)
{
  printf_filtered ("Tracepoint %d", tp->number);

  if (addressprint || (tp->source_file == NULL))
    {
      printf_filtered (" at ");
      print_address_numeric (tp->address, 1, gdb_stdout);
    }
  if (tp->source_file)
    printf_filtered (": file %s, line %d.",
		     tp->source_file, tp->line_number);

  printf_filtered ("\n");
}