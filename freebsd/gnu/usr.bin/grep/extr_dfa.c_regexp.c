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
 scalar_t__ OR ; 
 scalar_t__ ORTOP ; 
 int /*<<< orphan*/  addtok (scalar_t__) ; 
 int /*<<< orphan*/  branch () ; 
 scalar_t__ lex () ; 
 scalar_t__ tok ; 

__attribute__((used)) static void
regexp (int toplevel)
{
  branch();
  while (tok == OR)
    {
      tok = lex();
      branch();
      if (toplevel)
	addtok(ORTOP);
      else
	addtok(OR);
    }
}