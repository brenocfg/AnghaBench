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
 int /*<<< orphan*/ * e ; 
 int el_getc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * h ; 
 int /*<<< orphan*/  rl_initialize () ; 

int
rl_read_key(void)
{
	char fooarr[2 * sizeof(int)];

	if (e == NULL || h == NULL)
		rl_initialize();

	return el_getc(e, fooarr);
}