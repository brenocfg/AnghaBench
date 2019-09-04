#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* callback_os_window; } ;
struct TYPE_6__ {scalar_t__ left; scalar_t__ right; scalar_t__ top; scalar_t__ bottom; } ;
struct TYPE_5__ {scalar_t__ mouse_y; scalar_t__ mouse_x; } ;
typedef  TYPE_2__ Region ;

/* Variables and functions */
 TYPE_4__ global_state ; 

__attribute__((used)) static inline bool
mouse_in_region(Region *r) {
    if (r->left == r->right) return false;
    if (global_state.callback_os_window->mouse_y < r->top || global_state.callback_os_window->mouse_y > r->bottom) return false;
    if (global_state.callback_os_window->mouse_x < r->left || global_state.callback_os_window->mouse_x > r->right) return false;
    return true;
}