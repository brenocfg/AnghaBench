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
typedef  int /*<<< orphan*/ * an_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  atomic_store_rel_ptr (uintptr_t*,uintptr_t) ; 
 int /*<<< orphan*/ * t4_an_handler ; 

void
t4_register_an_handler(an_handler_t h)
{
	uintptr_t *loc;

	MPASS(h == NULL || t4_an_handler == NULL);

	loc = (uintptr_t *)&t4_an_handler;
	atomic_store_rel_ptr(loc, (uintptr_t)h);
}