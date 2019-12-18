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
 int /*<<< orphan*/  error (char*,unsigned int) ; 
 unsigned int input_radix ; 
 int /*<<< orphan*/  printf_filtered (char*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void
set_input_radix_1 (int from_tty, unsigned radix)
{
  /* We don't currently disallow any input radix except 0 or 1, which don't
     make any mathematical sense.  In theory, we can deal with any input
     radix greater than 1, even if we don't have unique digits for every
     value from 0 to radix-1, but in practice we lose on large radix values.
     We should either fix the lossage or restrict the radix range more.
     (FIXME). */

  if (radix < 2)
    {
      /* FIXME: cagney/2002-03-17: This needs to revert the bad radix
         value.  */
      error ("Nonsense input radix ``decimal %u''; input radix unchanged.",
	     radix);
    }
  input_radix = radix;
  if (from_tty)
    {
      printf_filtered ("Input radix now set to decimal %u, hex %x, octal %o.\n",
		       radix, radix, radix);
    }
}