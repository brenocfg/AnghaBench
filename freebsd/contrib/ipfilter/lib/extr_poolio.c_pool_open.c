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
 int /*<<< orphan*/  IPLOOKUP_NAME ; 
 int OPT_DONTOPEN ; 
 int /*<<< orphan*/  O_RDWR ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int opts ; 
 int poolfd ; 

int
pool_open()
{

	if ((opts & OPT_DONTOPEN) != 0)
		return 0;

	if (poolfd == -1)
		poolfd = open(IPLOOKUP_NAME, O_RDWR);
	return poolfd;
}