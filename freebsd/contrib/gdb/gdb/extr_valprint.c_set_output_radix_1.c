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
 char output_format ; 
 unsigned int output_radix ; 
 int /*<<< orphan*/  printf_filtered (char*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void
set_output_radix_1 (int from_tty, unsigned radix)
{
  /* Validate the radix and disallow ones that we aren't prepared to
     handle correctly, leaving the radix unchanged. */
  switch (radix)
    {
    case 16:
      output_format = 'x';	/* hex */
      break;
    case 10:
      output_format = 0;	/* decimal */
      break;
    case 8:
      output_format = 'o';	/* octal */
      break;
    default:
      /* FIXME: cagney/2002-03-17: This needs to revert the bad radix
         value.  */
      error ("Unsupported output radix ``decimal %u''; output radix unchanged.",
	     radix);
    }
  output_radix = radix;
  if (from_tty)
    {
      printf_filtered ("Output radix now set to decimal %u, hex %x, octal %o.\n",
		       radix, radix, radix);
    }
}