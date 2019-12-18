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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MSR_AMDK7_FIDVID_STATUS ; 
 scalar_t__ PN8_STA_PENDING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pn8_read_pending_wait(uint64_t *status)
{
	int i = 10000;

	do
		*status = rdmsr(MSR_AMDK7_FIDVID_STATUS);
	while (PN8_STA_PENDING(*status) && --i);

	return (i == 0 ? ENXIO : 0);
}