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
 int parse_and_eval_long (char*) ; 
 int /*<<< orphan*/  printf_filtered (char*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  set_input_radix_1 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  set_output_radix_1 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
set_radix (char *arg, int from_tty)
{
  unsigned radix;

  radix = (arg == NULL) ? 10 : parse_and_eval_long (arg);
  set_output_radix_1 (0, radix);
  set_input_radix_1 (0, radix);
  if (from_tty)
    {
      printf_filtered ("Input and output radices now set to decimal %u, hex %x, octal %o.\n",
		       radix, radix, radix);
    }
}