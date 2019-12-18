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
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ xdchange_t ;

/* Variables and functions */
 int /*<<< orphan*/  xdl_free (TYPE_1__*) ; 

void xdl_free_script(xdchange_t *xscr) {
	xdchange_t *xch;

	while ((xch = xscr) != NULL) {
		xscr = xscr->next;
		xdl_free(xch);
	}
}