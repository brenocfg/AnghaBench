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
 int /*<<< orphan*/  eval_string (char*) ; 
 char* pop_string () ; 

__attribute__((used)) static void
eval_tos(void)
{
	char *p;

	p = pop_string();
	if (p != NULL)
		eval_string(p);
}