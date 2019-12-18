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
 int /*<<< orphan*/  SLC_IMPORT ; 
 int /*<<< orphan*/  SLC_RVALUE ; 
 int /*<<< orphan*/  TELOPT_LINEMODE ; 
 scalar_t__ my_state_is_will (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slc_import (int) ; 
 int /*<<< orphan*/  slc_mode ; 

void
slc_mode_import(int def)
{
    slc_mode = def ? SLC_IMPORT : SLC_RVALUE;
    if (my_state_is_will(TELOPT_LINEMODE))
	slc_import(def);
}