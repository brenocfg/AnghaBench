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
struct TYPE_4__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ OSWindow ;

/* Variables and functions */
 scalar_t__ OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwPostEmptyEvent () ; 
 int /*<<< orphan*/  glfwRequestWindowAttention (int /*<<< orphan*/ ) ; 
 TYPE_1__* os_window_for_kitty_window (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ring_audio_bell (TYPE_1__*) ; 
 int /*<<< orphan*/  window_alert_on_bell ; 

void
request_window_attention(id_type kitty_window_id, bool audio_bell) {
    OSWindow *w = os_window_for_kitty_window(kitty_window_id);
    if (w) {
        if (audio_bell) ring_audio_bell(w);
        if (OPT(window_alert_on_bell)) glfwRequestWindowAttention(w->handle);
        glfwPostEmptyEvent();
    }
}