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
typedef  int xo_state_t ;
typedef  int /*<<< orphan*/  names ;

/* Variables and functions */

__attribute__((used)) static const char *
xo_state_name (xo_state_t state)
{
    static const char *names[] = {
	"init",
	"open_container",
	"close_container",
	"open_list",
	"close_list",
	"open_instance",
	"close_instance",
	"open_leaf_list",
	"close_leaf_list",
	"discarding",
	"marker",
	"emit",
	"emit_leaf_list",
	"finish",
	NULL
    };

    if (state < (sizeof(names) / sizeof(names[0])))
	return names[state];

    return "unknown";
}