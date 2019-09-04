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
typedef  int /*<<< orphan*/  id_type ;
struct TYPE_4__ {int /*<<< orphan*/  capacity; int /*<<< orphan*/  num_tabs; int /*<<< orphan*/  tabs; } ;
typedef  TYPE_1__ OSWindow ;

/* Variables and functions */
 int /*<<< orphan*/  REMOVER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tab ; 
 int /*<<< orphan*/  destroy_tab ; 
 int /*<<< orphan*/  make_os_window_context_current (TYPE_1__*) ; 

__attribute__((used)) static inline void
remove_tab_inner(OSWindow *os_window, id_type id) {
    make_os_window_context_current(os_window);
    REMOVER(os_window->tabs, id, os_window->num_tabs, Tab, destroy_tab, os_window->capacity);
}