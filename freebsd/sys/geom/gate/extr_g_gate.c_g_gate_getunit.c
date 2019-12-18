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
 int EEXIST ; 
 int EINVAL ; 
 int ENFILE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int g_gate_maxunits ; 
 int /*<<< orphan*/ ** g_gate_units ; 
 int /*<<< orphan*/  g_gate_units_lock ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_gate_getunit(int unit, int *errorp)
{

	mtx_assert(&g_gate_units_lock, MA_OWNED);
	if (unit >= 0) {
		if (unit >= g_gate_maxunits)
			*errorp = EINVAL;
		else if (g_gate_units[unit] == NULL)
			return (unit);
		else
			*errorp = EEXIST;
	} else {
		for (unit = 0; unit < g_gate_maxunits; unit++) {
			if (g_gate_units[unit] == NULL)
				return (unit);
		}
		*errorp = ENFILE;
	}
	return (-1);
}