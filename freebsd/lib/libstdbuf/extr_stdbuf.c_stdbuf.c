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
 int /*<<< orphan*/  change_buf (int /*<<< orphan*/ ,char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) __attribute__ ((constructor)) static void
stdbuf(void)
{
	char *i_mode, *o_mode, *e_mode;

	i_mode = getenv("_STDBUF_I");
	o_mode = getenv("_STDBUF_O");
	e_mode = getenv("_STDBUF_E");

	if (e_mode != NULL)
		change_buf(stderr, e_mode);
	if (i_mode != NULL)
		change_buf(stdin, i_mode);
	if (o_mode != NULL)
		change_buf(stdout, o_mode);
}