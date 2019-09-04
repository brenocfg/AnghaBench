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
struct TYPE_4__ {scalar_t__ inited; } ;
typedef  TYPE_1__ _GLFWIBUSData ;

/* Variables and functions */
 scalar_t__ GLFW_TRUE ; 
 int /*<<< orphan*/  setup_connection (TYPE_1__*) ; 
 int /*<<< orphan*/  test_env_var (char*,char*) ; 

void
glfw_connect_to_ibus(_GLFWIBUSData *ibus) {
    if (ibus->inited) return;
    if (!test_env_var("GLFW_IM_MODULE", "ibus")) return;
    ibus->inited = GLFW_TRUE;
    setup_connection(ibus);
}