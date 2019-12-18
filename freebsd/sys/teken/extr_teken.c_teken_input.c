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
typedef  int /*<<< orphan*/  teken_t ;

/* Variables and functions */
 int /*<<< orphan*/  teken_funcs_post_input (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  teken_funcs_pre_input (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  teken_input_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
teken_input(teken_t *t, const void *buf, size_t len)
{
	const char *c = buf;

	teken_funcs_pre_input(t);
	while (len-- > 0)
		teken_input_byte(t, *c++);
	teken_funcs_post_input(t);
}