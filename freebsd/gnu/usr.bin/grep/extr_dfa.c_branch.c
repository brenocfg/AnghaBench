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
 int /*<<< orphan*/  CAT ; 
 scalar_t__ OR ; 
 scalar_t__ RPAREN ; 
 int /*<<< orphan*/  addtok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closure () ; 
 scalar_t__ tok ; 

__attribute__((used)) static void
branch (void)
{
  closure();
  while (tok != RPAREN && tok != OR && tok >= 0)
    {
      closure();
      addtok(CAT);
    }
}