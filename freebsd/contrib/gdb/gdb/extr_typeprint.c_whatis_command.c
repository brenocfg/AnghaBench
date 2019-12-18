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
 int /*<<< orphan*/  whatis_exp (char*,int) ; 

__attribute__((used)) static void
whatis_command (char *exp, int from_tty)
{
  /* Most of the time users do not want to see all the fields
     in a structure.  If they do they can use the "ptype" command.
     Hence the "-1" below.  */
  whatis_exp (exp, -1);
}