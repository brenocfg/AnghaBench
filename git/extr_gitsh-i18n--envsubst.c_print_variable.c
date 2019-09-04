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
 int /*<<< orphan*/  fwrite (char const*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
print_variable (const char *var_ptr, size_t var_len)
{
  fwrite (var_ptr, var_len, 1, stdout);
  putchar ('\n');
}