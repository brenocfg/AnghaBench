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
typedef  int /*<<< orphan*/  input ;

/* Variables and functions */
 int /*<<< orphan*/  autoboot_maybe () ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 int /*<<< orphan*/  interp_emit_prompt () ; 
 int /*<<< orphan*/  interp_init () ; 
 int /*<<< orphan*/  interp_run (char*) ; 
 int /*<<< orphan*/  ngets (char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 

void
interact(void)
{
	static char	input[256];			/* big enough? */

	interp_init();

	printf("\n");

	/*
	 * Before interacting, we might want to autoboot.
	 */
	autoboot_maybe();

	/*
	 * Not autobooting, go manual
	 */
	printf("\nType '?' for a list of commands, 'help' for more detailed help.\n");
	if (getenv("prompt") == NULL)
		setenv("prompt", "${interpret}", 1);
	if (getenv("interpret") == NULL)
		setenv("interpret", "OK", 1);

	for (;;) {
		input[0] = '\0';
		interp_emit_prompt();
		ngets(input, sizeof(input));
		interp_run(input);
	}
}