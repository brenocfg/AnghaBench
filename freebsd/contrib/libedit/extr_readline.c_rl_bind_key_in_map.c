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
typedef  int /*<<< orphan*/  rl_command_func_t ;
typedef  int /*<<< orphan*/  Keymap ;

/* Variables and functions */

int
/*ARGSUSED*/
rl_bind_key_in_map(int key __attribute__((__unused__)),
    rl_command_func_t *fun __attribute__((__unused__)),
    Keymap k __attribute__((__unused__)))
{
	return 0;
}