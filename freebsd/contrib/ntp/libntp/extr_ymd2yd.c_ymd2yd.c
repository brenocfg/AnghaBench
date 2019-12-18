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
 int ntpcal_edate_to_yeardays (int,int,int) ; 

int
ymd2yd(
	int y,
	int m,
	int d)
{
	/*
	 * convert y/m/d to elapsed calendar units, convert that to
	 * elapsed days since the start of the given year and convert
	 * back to unity-based day in year.
	 *
	 * This does no further error checking, since the underlying
	 * function is assumed to work out how to handle the data.
	 */
	return ntpcal_edate_to_yeardays(y-1, m-1, d-1) + 1;
}