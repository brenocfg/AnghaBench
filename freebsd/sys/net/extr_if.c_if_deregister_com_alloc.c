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
typedef  size_t u_char ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ ** if_com_alloc ; 
 int /*<<< orphan*/ ** if_com_free ; 

void
if_deregister_com_alloc(u_char type)
{
	
	KASSERT(if_com_alloc[type] != NULL,
	    ("if_deregister_com_alloc: %d not registered", type));
	KASSERT(if_com_free[type] != NULL,
	    ("if_deregister_com_alloc: %d free not registered", type));
	if_com_alloc[type] = NULL;
	if_com_free[type] = NULL;
}