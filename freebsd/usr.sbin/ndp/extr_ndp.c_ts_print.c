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
typedef  int u_int32_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int,int,int) ; 
 int thiszone ; 

__attribute__((used)) static void
ts_print(const struct timeval *tvp)
{
	int sec;

	/* Default */
	sec = (tvp->tv_sec + thiszone) % 86400;
	(void)printf("%02d:%02d:%02d.%06u ",
	    sec / 3600, (sec % 3600) / 60, sec % 60, (u_int32_t)tvp->tv_usec);
}