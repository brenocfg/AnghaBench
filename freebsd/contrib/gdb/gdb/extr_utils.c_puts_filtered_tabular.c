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
 int UINT_MAX ; 
 char* alloca (int) ; 
 int chars_per_line ; 
 int chars_printed ; 
 int /*<<< orphan*/  fputs_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int strlen (char*) ; 

void
puts_filtered_tabular (char *string, int width, int right)
{
  int spaces = 0;
  int stringlen;
  char *spacebuf;

  gdb_assert (chars_per_line > 0);
  if (chars_per_line == UINT_MAX)
    {
      fputs_filtered (string, gdb_stdout);
      fputs_filtered ("\n", gdb_stdout);
      return;
    }

  if (((chars_printed - 1) / width + 2) * width >= chars_per_line)
    fputs_filtered ("\n", gdb_stdout);

  if (width >= chars_per_line)
    width = chars_per_line - 1;

  stringlen = strlen (string);

  if (chars_printed > 0)
    spaces = width - (chars_printed - 1) % width - 1;
  if (right)
    spaces += width - stringlen;

  spacebuf = alloca (spaces + 1);
  spacebuf[spaces] = '\0';
  while (spaces--)
    spacebuf[spaces] = ' ';

  fputs_filtered (spacebuf, gdb_stdout);
  fputs_filtered (string, gdb_stdout);
}