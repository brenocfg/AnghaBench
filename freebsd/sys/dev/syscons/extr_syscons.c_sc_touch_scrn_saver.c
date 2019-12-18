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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  run_scrn_saver ; 
 int /*<<< orphan*/  scsplash_stick (int /*<<< orphan*/ ) ; 

void
sc_touch_scrn_saver(void)
{
    scsplash_stick(FALSE);
    run_scrn_saver = FALSE;
}