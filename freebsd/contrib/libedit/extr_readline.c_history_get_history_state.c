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
struct TYPE_4__ {int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ HISTORY_STATE ;

/* Variables and functions */
 TYPE_1__* el_malloc (int) ; 
 int /*<<< orphan*/  history_length ; 

HISTORY_STATE *
history_get_history_state(void)
{
	HISTORY_STATE *hs;

	if ((hs = el_malloc(sizeof(*hs))) == NULL)
		return NULL;
	hs->length = history_length;
	return hs;
}