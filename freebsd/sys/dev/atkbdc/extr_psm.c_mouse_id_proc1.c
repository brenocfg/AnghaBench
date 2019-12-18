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
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int get_mouse_status (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 
 int set_mouse_resolution (int /*<<< orphan*/ ,int) ; 
 scalar_t__ set_mouse_scaling (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mouse_id_proc1(KBDC kbdc, int res, int scale, int *status)
{
	if (set_mouse_resolution(kbdc, res) != res)
		return (FALSE);
	if (set_mouse_scaling(kbdc, scale) &&
	    set_mouse_scaling(kbdc, scale) &&
	    set_mouse_scaling(kbdc, scale) &&
	    (get_mouse_status(kbdc, status, 0, 3) >= 3))
		return (TRUE);
	return (FALSE);
}