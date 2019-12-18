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
 int /*<<< orphan*/  H_INT_ESB ; 
 int PLPAR_HCALL_BUFSIZE ; 
 scalar_t__ plpar_busy_delay (long) ; 
 long plpar_hcall (int /*<<< orphan*/ ,unsigned long*,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pr_devel (char*,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long,unsigned long,long) ; 

__attribute__((used)) static long plpar_int_esb(unsigned long flags,
			  unsigned long lisn,
			  unsigned long offset,
			  unsigned long in_data,
			  unsigned long *out_data)
{
	unsigned long retbuf[PLPAR_HCALL_BUFSIZE];
	long rc;

	pr_devel("H_INT_ESB flags=%lx lisn=%lx offset=%lx in=%lx\n",
		flags,  lisn, offset, in_data);

	do {
		rc = plpar_hcall(H_INT_ESB, retbuf, flags, lisn, offset,
				 in_data);
	} while (plpar_busy_delay(rc));

	if (rc) {
		pr_err("H_INT_ESB lisn=%ld offset=%ld returned %ld\n",
		       lisn, offset, rc);
		return  rc;
	}

	*out_data = retbuf[0];

	return 0;
}