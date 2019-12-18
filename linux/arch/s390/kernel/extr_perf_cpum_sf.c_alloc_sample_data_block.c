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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long SDB_TE_ALERT_REQ_MASK ; 
 unsigned long get_zeroed_page (int /*<<< orphan*/ ) ; 
 unsigned long* trailer_entry_ptr (unsigned long) ; 

__attribute__((used)) static int alloc_sample_data_block(unsigned long *sdbt, gfp_t gfp_flags)
{
	unsigned long sdb, *trailer;

	/* Allocate and initialize sample-data-block */
	sdb = get_zeroed_page(gfp_flags);
	if (!sdb)
		return -ENOMEM;
	trailer = trailer_entry_ptr(sdb);
	*trailer = SDB_TE_ALERT_REQ_MASK;

	/* Link SDB into the sample-data-block-table */
	*sdbt = sdb;

	return 0;
}