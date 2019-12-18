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
struct TYPE_4__ {int /*<<< orphan*/  cmd_name; } ;
typedef  TYPE_1__ ENGINE_CMD_DEFN ;

/* Variables and functions */
 scalar_t__ int_ctrl_cmd_is_null (TYPE_1__ const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int int_ctrl_cmd_by_name(const ENGINE_CMD_DEFN *defn, const char *s)
{
    int idx = 0;
    while (!int_ctrl_cmd_is_null(defn) && (strcmp(defn->cmd_name, s) != 0)) {
        idx++;
        defn++;
    }
    if (int_ctrl_cmd_is_null(defn))
        /* The given name wasn't found */
        return -1;
    return idx;
}