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
 int /*<<< orphan*/  e ; 
 int /*<<< orphan*/  el_insertstr (int /*<<< orphan*/ ,char*) ; 

int
rl_stuff_char(int c)
{
	char buf[2];

	buf[0] = (char)c;
	buf[1] = '\0';
	el_insertstr(e, buf);
	return 1;
}