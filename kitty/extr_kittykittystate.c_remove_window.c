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
typedef  int /*<<< orphan*/  id_type ;

/* Variables and functions */
 int /*<<< orphan*/  END_WITH_TAB ; 
 int /*<<< orphan*/  WITH_TAB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_os_window_context_current (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osw ; 
 int /*<<< orphan*/  remove_window_inner (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tab ; 

__attribute__((used)) static inline void
remove_window(id_type os_window_id, id_type tab_id, id_type id) {
    WITH_TAB(os_window_id, tab_id);
        make_os_window_context_current(osw);
        remove_window_inner(tab, id);
    END_WITH_TAB;
}