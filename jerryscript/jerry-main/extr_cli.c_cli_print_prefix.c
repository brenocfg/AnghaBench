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
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cli_print_prefix (const char *str, /**< string to print */
                  int len) /**< length of the prefix to print */
{
  for (int i = 0; i < len; i++)
  {
    printf ("%c", *str++);
  }
}