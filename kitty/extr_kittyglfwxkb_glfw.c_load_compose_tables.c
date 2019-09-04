#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xkb_compose_table {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  composeState; } ;
struct TYPE_5__ {TYPE_1__ states; int /*<<< orphan*/  context; } ;
typedef  TYPE_2__ _GLFWXKBData ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  XKB_COMPOSE_COMPILE_NO_FLAGS ; 
 int /*<<< orphan*/  XKB_COMPOSE_STATE_NO_FLAGS ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,...) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  xkb_compose_state_new (struct xkb_compose_table*,int /*<<< orphan*/ ) ; 
 struct xkb_compose_table* xkb_compose_table_new_from_locale (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xkb_compose_table_unref (struct xkb_compose_table*) ; 

__attribute__((used)) static void
load_compose_tables(_GLFWXKBData *xkb) {
    /* Look up the preferred locale, falling back to "C" as default. */
    struct xkb_compose_table* compose_table = NULL;
    const char *locale = getenv("LC_ALL");
    if (!locale) locale = getenv("LC_CTYPE");
    if (!locale) locale = getenv("LANG");
    if (!locale) locale = "C";
    compose_table = xkb_compose_table_new_from_locale(xkb->context, locale, XKB_COMPOSE_COMPILE_NO_FLAGS);
    if (!compose_table) {
        _glfwInputError(GLFW_PLATFORM_ERROR, "Failed to create XKB compose table for locale %s", locale);
        return;
    }
    xkb->states.composeState = xkb_compose_state_new(compose_table, XKB_COMPOSE_STATE_NO_FLAGS);
    if (!xkb->states.composeState) {
        _glfwInputError(GLFW_PLATFORM_ERROR, "Failed to create XKB compose state");
    }
    xkb_compose_table_unref(compose_table);
}