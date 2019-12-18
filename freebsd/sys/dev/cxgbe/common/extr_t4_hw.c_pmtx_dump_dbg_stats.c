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
typedef  int /*<<< orphan*/  u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  A_PM_TX_DBG_CTRL ; 
 int /*<<< orphan*/  A_PM_TX_DBG_DATA ; 
 scalar_t__ A_PM_TX_DBG_STAT0 ; 
 int /*<<< orphan*/  CH_ALERT (struct adapter*,char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_read_indirect (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__) ; 

__attribute__((used)) static bool pmtx_dump_dbg_stats(struct adapter *adap, int arg, bool verbose)
{
	int i;
	u32 data[17];

	t4_read_indirect(adap, A_PM_TX_DBG_CTRL, A_PM_TX_DBG_DATA, &data[0],
	    ARRAY_SIZE(data), A_PM_TX_DBG_STAT0);
	for (i = 0; i < ARRAY_SIZE(data); i++) {
		CH_ALERT(adap, "  - PM_TX_DBG_STAT%u (0x%x) = 0x%08x\n", i,
		    A_PM_TX_DBG_STAT0 + i, data[i]);
	}

	return (false);
}