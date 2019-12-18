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
 int /*<<< orphan*/  PUTX (char) ; 

__attribute__((used)) static int
print_filename (char *to_print, char *full_pathname)
{
  int printed_len = 0;
  char *s;

  for (s = to_print; *s; s++)
    {
      PUTX (*s);
    }
  return printed_len;
}