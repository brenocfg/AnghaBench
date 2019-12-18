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
struct scroll_tab_list {struct scroll_tab_list* next; int /*<<< orphan*/  element; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  Strsave (int /*<<< orphan*/ *) ; 
 struct scroll_tab_list* scroll_tab ; 
 struct scroll_tab_list* xmalloc (int) ; 

__attribute__((used)) static void
add_scroll_tab(Char *item)
{
    struct scroll_tab_list *new_scroll;

    new_scroll = xmalloc(sizeof(struct scroll_tab_list));
    new_scroll->element = Strsave(item);
    new_scroll->next = scroll_tab;
    scroll_tab = new_scroll;
}