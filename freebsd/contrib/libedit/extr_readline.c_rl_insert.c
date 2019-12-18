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
 int /*<<< orphan*/  el_push (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * h ; 
 int /*<<< orphan*/  rl_initialize () ; 

int
rl_insert(int count, int c)
{
	char arr[2];

	if (h == NULL || e == NULL)
		rl_initialize();

	/* XXX - int -> char conversion can lose on multichars */
	arr[0] = (char)c;
	arr[1] = '\0';

	for (; count > 0; count--)
		el_push(e, arr);

	return 0;
}