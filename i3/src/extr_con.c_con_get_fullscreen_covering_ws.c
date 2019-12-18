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
 int /*<<< orphan*/  CF_GLOBAL ; 
 int /*<<< orphan*/  CF_OUTPUT ; 
 int /*<<< orphan*/ * con_get_fullscreen_con (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * croot ; 

Con *con_get_fullscreen_covering_ws(Con *ws) {
    if (!ws) {
        return NULL;
    }
    Con *fs = con_get_fullscreen_con(croot, CF_GLOBAL);
    if (!fs) {
        return con_get_fullscreen_con(ws, CF_OUTPUT);
    }
    return fs;
}