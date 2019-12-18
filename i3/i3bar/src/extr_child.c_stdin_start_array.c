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

/* Variables and functions */
 int /*<<< orphan*/  clear_statusline (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  statusline_buffer ; 

__attribute__((used)) static int stdin_start_array(void *context) {
    // the blocks are still used by statusline_head, so we won't free the
    // resources here.
    clear_statusline(&statusline_buffer, false);
    return 1;
}