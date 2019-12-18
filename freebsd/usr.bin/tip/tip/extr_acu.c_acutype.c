#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * acu_name; } ;
typedef  TYPE_1__ acu_t ;

/* Variables and functions */
 TYPE_1__* NOACU ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static acu_t *
acutype(char *s)
{
	acu_t *p;
	extern acu_t acutable[];

	for (p = acutable; p->acu_name != NULL; p++)
		if (!strcmp(s, p->acu_name))
			return (p);
	return (NOACU);
}