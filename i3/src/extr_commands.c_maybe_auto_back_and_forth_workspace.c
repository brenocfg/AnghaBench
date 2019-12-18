#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  workspace_auto_back_and_forth; } ;
typedef  int /*<<< orphan*/  Con ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*) ; 
 int /*<<< orphan*/ * con_get_workspace (int /*<<< orphan*/ ) ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  focused ; 
 int /*<<< orphan*/ * workspace_back_and_forth_get () ; 

__attribute__((used)) static Con *maybe_auto_back_and_forth_workspace(Con *workspace) {
    Con *current, *baf;

    if (!config.workspace_auto_back_and_forth)
        return workspace;

    current = con_get_workspace(focused);

    if (current == workspace) {
        baf = workspace_back_and_forth_get();
        if (baf != NULL) {
            DLOG("Substituting workspace with back_and_forth, as it is focused.\n");
            return baf;
        }
    }

    return workspace;
}