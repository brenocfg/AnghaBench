#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct proc {TYPE_1__* p_args; } ;
struct TYPE_2__ {char* ar_args; scalar_t__ ar_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  db_printf (char*,...) ; 

__attribute__((used)) static void
dump_args(volatile struct proc *p)
{
	char *args;
	int i, len;

	if (p->p_args == NULL)
		return;
	args = p->p_args->ar_args;
	len = (int)p->p_args->ar_length;
	for (i = 0; i < len; i++) {
		if (args[i] == '\0')
			db_printf(" ");
		else
			db_printf("%c", args[i]);
	}
}