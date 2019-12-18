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
 scalar_t__ isdigit (char) ; 

__attribute__((used)) static int
process_reference (char **string)
{
  char *p;
  int refnum = 0;

  if (**string != '#')
    return 0;

  /* Advance beyond the initial '#'.  */
  p = *string + 1;

  /* Read number as reference id. */
  while (*p && isdigit (*p))
    {
      refnum = refnum * 10 + *p - '0';
      p++;
    }
  *string = p;
  return refnum;
}