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
 int /*<<< orphan*/  find_variables (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_variable ; 

__attribute__((used)) static void
print_variables (const char *string)
{
  find_variables (string, &print_variable);
}