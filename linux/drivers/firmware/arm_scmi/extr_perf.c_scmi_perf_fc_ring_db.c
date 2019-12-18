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
typedef  int u64 ;
struct scmi_fc_db_info {int width; int mask; int /*<<< orphan*/  addr; int /*<<< orphan*/  set; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCMI_PERF_FC_RING_DB (int) ; 
 int ioread64_hi_lo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite64_hi_lo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scmi_perf_fc_ring_db(struct scmi_fc_db_info *db)
{
	if (!db || !db->addr)
		return;

	if (db->width == 1)
		SCMI_PERF_FC_RING_DB(8);
	else if (db->width == 2)
		SCMI_PERF_FC_RING_DB(16);
	else if (db->width == 4)
		SCMI_PERF_FC_RING_DB(32);
	else /* db->width == 8 */
#ifdef CONFIG_64BIT
		SCMI_PERF_FC_RING_DB(64);
#else
	{
		u64 val = 0;

		if (db->mask)
			val = ioread64_hi_lo(db->addr) & db->mask;
		iowrite64_hi_lo(db->set, db->addr);
	}
#endif
}