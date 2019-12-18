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
typedef  int /*<<< orphan*/  u_int ;
struct timespec {int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  fattime2timespec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct timespec*) ; 
 int /*<<< orphan*/  smb_time_server2local (int /*<<< orphan*/ ,int,struct timespec*) ; 

void
smb_dos2unixtime(u_int dd, u_int dt, u_int dh, int tzoff,
	struct timespec *tsp)
{

	fattime2timespec(dd, dt, dh, 1, tsp);
	smb_time_server2local(tsp->tv_sec, tzoff, tsp);
}