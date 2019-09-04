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
typedef  int /*<<< orphan*/  Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/ * alloc_cursor () ; 
 int /*<<< orphan*/  cursor_copy_to (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

Cursor*
cursor_copy(Cursor *self) {
    Cursor* ans;
    ans = alloc_cursor();
    if (ans == NULL) { PyErr_NoMemory(); return NULL; }
    cursor_copy_to(self, ans);
    return ans;
}