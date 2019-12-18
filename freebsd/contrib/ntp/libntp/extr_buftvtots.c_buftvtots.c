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
typedef  int /*<<< orphan*/  tv ;
struct timeval {int tv_usec; } ;
typedef  int /*<<< orphan*/  l_fp ;

/* Variables and functions */
 int FALSE ; 
 int MICROSECONDS ; 
 int TRUE ; 
 int /*<<< orphan*/  memcpy (struct timeval*,char const*,int) ; 
 int /*<<< orphan*/  tval_stamp_to_lfp (struct timeval) ; 

int
buftvtots(
	const char *bufp,
	l_fp *ts
	)
{
	struct timeval tv;

	/*
	 * copy to adhere to alignment restrictions
	 */
	memcpy(&tv, bufp, sizeof(tv));

	/*
	 * and use it
	 */
	if (tv.tv_usec > MICROSECONDS - 1)
		return FALSE;

	*ts = tval_stamp_to_lfp(tv);

	return TRUE;
}