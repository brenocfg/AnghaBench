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
typedef  int /*<<< orphan*/  Output ;

/* Variables and functions */
 int /*<<< orphan*/  D_DOWN ; 
 int /*<<< orphan*/  D_LEFT ; 
 int /*<<< orphan*/  D_RIGHT ; 
 int /*<<< orphan*/  D_UP ; 
 int /*<<< orphan*/  focused ; 
 int /*<<< orphan*/ * get_output_by_name (char const*,int) ; 
 int /*<<< orphan*/ * get_output_for_con (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_output_next_wrap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

Output *get_output_from_string(Output *current_output, const char *output_str) {
    if (strcasecmp(output_str, "current") == 0) {
        return get_output_for_con(focused);
    } else if (strcasecmp(output_str, "left") == 0) {
        return get_output_next_wrap(D_LEFT, current_output);
    } else if (strcasecmp(output_str, "right") == 0) {
        return get_output_next_wrap(D_RIGHT, current_output);
    } else if (strcasecmp(output_str, "up") == 0) {
        return get_output_next_wrap(D_UP, current_output);
    } else if (strcasecmp(output_str, "down") == 0) {
        return get_output_next_wrap(D_DOWN, current_output);
    }

    return get_output_by_name(output_str, true);
}