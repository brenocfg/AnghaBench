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
struct TYPE_5__ {int /*<<< orphan*/ * el_vdisplay; int /*<<< orphan*/ * el_display; } ;
typedef  TYPE_1__ EditLine ;

/* Variables and functions */
 void* terminal_alloc_buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  terminal_free_display (TYPE_1__*) ; 

__attribute__((used)) static int
terminal_alloc_display(EditLine *el)
{
	el->el_display = terminal_alloc_buffer(el);
	if (el->el_display == NULL)
		goto done;
	el->el_vdisplay = terminal_alloc_buffer(el);
	if (el->el_vdisplay == NULL)
		goto done;
	return 0;
done:
	terminal_free_display(el);
	return -1;
}