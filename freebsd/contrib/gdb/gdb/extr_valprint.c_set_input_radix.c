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
struct cmd_list_element {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_radix ; 
 int /*<<< orphan*/  set_input_radix_1 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_input_radix (char *args, int from_tty, struct cmd_list_element *c)
{
  set_input_radix_1 (from_tty, input_radix);
}