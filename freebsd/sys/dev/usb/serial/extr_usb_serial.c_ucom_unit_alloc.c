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
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int alloc_unr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ucom_unrhdr ; 

__attribute__((used)) static int
ucom_unit_alloc(void)
{
	int unit;

	/* sanity checks */
	if (ucom_unrhdr == NULL) {
		DPRINTF("ucom_unrhdr is NULL\n");
		return (-1);
	}
	unit = alloc_unr(ucom_unrhdr);
	DPRINTF("unit %d is allocated\n", unit);
	return (unit);
}