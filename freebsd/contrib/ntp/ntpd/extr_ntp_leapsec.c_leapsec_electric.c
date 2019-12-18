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
 int _electric ; 
 int /*<<< orphan*/ * _lptr ; 
 int /*<<< orphan*/ * _ltab ; 
 int /*<<< orphan*/  reset_times (int /*<<< orphan*/ *) ; 

int/*BOOL*/
leapsec_electric(
	int/*BOOL*/ on)
{
	int res = _electric;
	if (on < 0)
		return res;

	_electric = (on != 0);
	if (_electric == res)
		return res;

	if (_lptr == &_ltab[0] || _lptr == &_ltab[1])
		reset_times(_lptr);

	return res;
}