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
typedef  int /*<<< orphan*/  rl_vcpfunc_t ;

/* Variables and functions */
 int /*<<< orphan*/  EL_UNBUFFERED ; 
 int /*<<< orphan*/ * e ; 
 int /*<<< orphan*/  el_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rl_initialize () ; 
 int /*<<< orphan*/ * rl_linefunc ; 
 int /*<<< orphan*/  rl_set_prompt (char const*) ; 

void
rl_callback_handler_install(const char *prompt, rl_vcpfunc_t *linefunc)
{
	if (e == NULL) {
		rl_initialize();
	}
	(void)rl_set_prompt(prompt);
	rl_linefunc = linefunc;
	el_set(e, EL_UNBUFFERED, 1);
}