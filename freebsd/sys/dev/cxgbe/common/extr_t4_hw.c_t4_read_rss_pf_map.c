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
 int /*<<< orphan*/  A_TP_RSS_PF_MAP ; 
 int /*<<< orphan*/  t4_tp_pio_read (struct adapter*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

u32 t4_read_rss_pf_map(struct adapter *adapter, bool sleep_ok)
{
	u32 pfmap;

	t4_tp_pio_read(adapter, &pfmap, 1, A_TP_RSS_PF_MAP, sleep_ok);

	return pfmap;
}