#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  freq_info ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int id32; scalar_t__ vendor_id; size_t tablen; int /*<<< orphan*/ * freqtab; } ;
typedef  TYPE_1__ cpu_info ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 TYPE_1__* ESTprocs ; 
 scalar_t__ cpu_vendor_id ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * est_get_current (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
est_table_info(device_t dev, uint64_t msr, freq_info **freqs, size_t *freqslen)
{
	cpu_info *p;
	uint32_t id;

	/* Find a table which matches (vendor, id32). */
	id = msr >> 32;
	for (p = ESTprocs; p->id32 != 0; p++) {
		if (p->vendor_id == cpu_vendor_id && p->id32 == id)
			break;
	}
	if (p->id32 == 0)
		return (EOPNOTSUPP);

	/* Make sure the current setpoint is valid. */
	if (est_get_current(p->freqtab, p->tablen) == NULL) {
		device_printf(dev, "current setting not found in table\n");
		return (EOPNOTSUPP);
	}

	*freqs = p->freqtab;
	*freqslen = p->tablen;
	return (0);
}