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
 scalar_t__ nfsrv_testmalloclimit ; 
 int /*<<< orphan*/  printf (char*) ; 

int
nfsrv_mallocmget_limit(void)
{
	static int printmesg = 0;
	static int testval = 1;

	if (nfsrv_testmalloclimit && (testval++ % 1000) == 0) {
		if ((printmesg++ % 100) == 0)
			printf("nfsd: malloc/mget near limit\n");
		return (1);
	}
	return (0);
}