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
 int /*<<< orphan*/  H_INT_GET_SOURCE_INFO ; 
 int PLPAR_HCALL_BUFSIZE ; 
 scalar_t__ plpar_busy_delay (long) ; 
 long plpar_hcall (int /*<<< orphan*/ ,unsigned long*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pr_devel (char*,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long,long) ; 

__attribute__((used)) static long plpar_int_get_source_info(unsigned long flags,
				      unsigned long lisn,
				      unsigned long *src_flags,
				      unsigned long *eoi_page,
				      unsigned long *trig_page,
				      unsigned long *esb_shift)
{
	unsigned long retbuf[PLPAR_HCALL_BUFSIZE];
	long rc;

	do {
		rc = plpar_hcall(H_INT_GET_SOURCE_INFO, retbuf, flags, lisn);
	} while (plpar_busy_delay(rc));

	if (rc) {
		pr_err("H_INT_GET_SOURCE_INFO lisn=%ld failed %ld\n", lisn, rc);
		return rc;
	}

	*src_flags = retbuf[0];
	*eoi_page  = retbuf[1];
	*trig_page = retbuf[2];
	*esb_shift = retbuf[3];

	pr_devel("H_INT_GET_SOURCE_INFO flags=%lx eoi=%lx trig=%lx shift=%lx\n",
		retbuf[0], retbuf[1], retbuf[2], retbuf[3]);

	return 0;
}