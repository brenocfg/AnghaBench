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
typedef  int /*<<< orphan*/  u_long ;
struct timespec {int dummy; } ;
typedef  scalar_t__ seconds ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF1970TO1601 ; 
 int /*<<< orphan*/  smb_time_local2server (struct timespec*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
smb_time_local2NT(struct timespec *tsp, int tzoff, int64_t *nsec)
{
	u_long seconds;

	smb_time_local2server(tsp, 0, &seconds);
	*nsec = (((int64_t)(seconds) & ~1) + DIFF1970TO1601) * (int64_t)10000000;
}