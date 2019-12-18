#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* symbol; } ;
typedef  TYPE_1__ collelem_t ;

/* Variables and functions */
 TYPE_1__* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  elem_by_symbol ; 

collelem_t *
lookup_collelem(char *symbol)
{
	collelem_t	srch;

	srch.symbol = symbol;
	return (RB_FIND(elem_by_symbol, &elem_by_symbol, &srch));
}