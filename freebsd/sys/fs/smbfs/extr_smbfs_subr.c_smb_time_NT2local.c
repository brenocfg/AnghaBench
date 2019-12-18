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
struct timespec {int dummy; } ;
typedef  int int64_t ;

/* Variables and functions */
 scalar_t__ DIFF1970TO1601 ; 
 int /*<<< orphan*/  smb_time_server2local (scalar_t__,int /*<<< orphan*/ ,struct timespec*) ; 

void
smb_time_NT2local(int64_t nsec, int tzoff, struct timespec *tsp)
{
	smb_time_server2local(nsec / 10000000 - DIFF1970TO1601, 0, tsp);
}