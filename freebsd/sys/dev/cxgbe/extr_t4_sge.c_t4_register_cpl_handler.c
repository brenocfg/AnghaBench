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
typedef  int /*<<< orphan*/ * cpl_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  atomic_store_rel_ptr (uintptr_t*,uintptr_t) ; 
 int nitems (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** t4_cpl_handler ; 

void
t4_register_cpl_handler(int opcode, cpl_handler_t h)
{
	uintptr_t *loc;

	MPASS(opcode < nitems(t4_cpl_handler));
	MPASS(h == NULL || t4_cpl_handler[opcode] == NULL);

	loc = (uintptr_t *)&t4_cpl_handler[opcode];
	atomic_store_rel_ptr(loc, (uintptr_t)h);
}