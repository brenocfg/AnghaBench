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
 int /*<<< orphan*/  el_push (int /*<<< orphan*/ ,char*) ; 

int
rl_get_previous_history(int count, int key)
{
	char a[2];
	a[0] = (char)key;
	a[1] = '\0';
	while (count--)
		el_push(e, a);
	return 0;
}