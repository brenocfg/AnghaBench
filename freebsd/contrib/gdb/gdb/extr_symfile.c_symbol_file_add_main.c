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
 int /*<<< orphan*/  symbol_file_add_main_1 (char*,int,int /*<<< orphan*/ ) ; 

void
symbol_file_add_main (char *args, int from_tty)
{
  symbol_file_add_main_1 (args, from_tty, 0);
}