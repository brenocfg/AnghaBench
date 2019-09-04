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
struct TYPE_3__ {scalar_t__ handle; } ;
typedef  TYPE_1__ OSWindow ;

/* Variables and functions */
 int /*<<< orphan*/  glfwWindowBell (scalar_t__) ; 
 double monotonic () ; 

void
ring_audio_bell(OSWindow *w) {
    static double last_bell_at = -1;
    double now = monotonic();
    if (now - last_bell_at <= 0.1) return;
    last_bell_at = now;
    if (w->handle) {
        glfwWindowBell(w->handle);
    }
}