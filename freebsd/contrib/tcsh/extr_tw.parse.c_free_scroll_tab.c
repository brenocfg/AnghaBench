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
struct scroll_tab_list {struct scroll_tab_list* element; struct scroll_tab_list* next; } ;

/* Variables and functions */
 struct scroll_tab_list* scroll_tab ; 
 int /*<<< orphan*/  xfree (struct scroll_tab_list*) ; 

__attribute__((used)) static void
free_scroll_tab(void)
{
    struct scroll_tab_list *loop;

    while(scroll_tab) {
	loop = scroll_tab;
	scroll_tab = scroll_tab->next;
	xfree(loop->element);
	xfree(loop);
    }
}