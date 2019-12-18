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
typedef  int /*<<< orphan*/  Con ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*) ; 
 int /*<<< orphan*/  previous_workspace_name ; 
 int /*<<< orphan*/ * workspace_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

Con *workspace_back_and_forth_get(void) {
    if (!previous_workspace_name) {
        DLOG("No previous workspace name set.\n");
        return NULL;
    }

    Con *workspace;
    workspace = workspace_get(previous_workspace_name, NULL);

    return workspace;
}