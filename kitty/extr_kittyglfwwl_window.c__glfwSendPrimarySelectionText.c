#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct zwp_primary_selection_source_v1 {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  primarySelectionString; } ;
struct TYPE_4__ {TYPE_1__ wl; } ;

/* Variables and functions */
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  send_text (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _glfwSendPrimarySelectionText(void *data, struct zwp_primary_selection_source_v1 *primary_selection_source,
        const char *mime_type, int fd) {
    send_text(_glfw.wl.primarySelectionString, fd);
}