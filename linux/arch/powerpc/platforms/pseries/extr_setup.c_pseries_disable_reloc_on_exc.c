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
 int /*<<< orphan*/  H_IS_LONG_BUSY (long) ; 
 long H_SUCCESS ; 
 long disable_reloc_on_exceptions () ; 
 int /*<<< orphan*/  get_longbusy_msecs (long) ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,long) ; 

void pseries_disable_reloc_on_exc(void)
{
	long rc;

	while (1) {
		rc = disable_reloc_on_exceptions();
		if (!H_IS_LONG_BUSY(rc))
			break;
		mdelay(get_longbusy_msecs(rc));
	}
	if (rc != H_SUCCESS)
		pr_warn("Warning: Failed to disable relocation on exceptions: %ld\n",
			rc);
}