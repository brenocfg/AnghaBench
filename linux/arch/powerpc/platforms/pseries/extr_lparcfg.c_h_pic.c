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
 int /*<<< orphan*/  H_PIC ; 
 int PLPAR_HCALL_BUFSIZE ; 
 unsigned long plpar_hcall (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static unsigned h_pic(unsigned long *pool_idle_time,
		      unsigned long *num_procs)
{
	unsigned long rc;
	unsigned long retbuf[PLPAR_HCALL_BUFSIZE];

	rc = plpar_hcall(H_PIC, retbuf);

	*pool_idle_time = retbuf[0];
	*num_procs = retbuf[1];

	return rc;
}