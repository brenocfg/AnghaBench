#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  id_type ;
struct TYPE_3__ {int /*<<< orphan*/  capacity; int /*<<< orphan*/  num_windows; int /*<<< orphan*/  windows; } ;
typedef  TYPE_1__ Tab ;

/* Variables and functions */
 int /*<<< orphan*/  REMOVER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Window ; 
 int /*<<< orphan*/  destroy_window ; 

__attribute__((used)) static inline void
remove_window_inner(Tab *tab, id_type id) {
    REMOVER(tab->windows, id, tab->num_windows, Window, destroy_window, tab->capacity);
}