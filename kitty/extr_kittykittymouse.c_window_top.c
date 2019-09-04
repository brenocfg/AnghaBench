#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {double top; } ;
struct TYPE_7__ {TYPE_1__ geometry; } ;
typedef  TYPE_2__ Window ;
struct TYPE_8__ {double logical_dpi_y; } ;
typedef  TYPE_3__ OSWindow ;

/* Variables and functions */
 double OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  window_padding_width ; 

__attribute__((used)) static inline double
window_top(Window *w, OSWindow *os_window) {
    return w->geometry.top - OPT(window_padding_width) * (os_window->logical_dpi_y / 72.0);
}