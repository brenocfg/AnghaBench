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
typedef  int /*<<< orphan*/  u16 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_LKPTBLQUEUE0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_LKPTBLQUEUE1 (int /*<<< orphan*/ ) ; 
 int RSS_NENTRIES ; 
 int rd_rss_row (struct adapter*,int,int /*<<< orphan*/ *) ; 

int t4_read_rss(struct adapter *adapter, u16 *map)
{
	u32 val;
	int i, ret;

	for (i = 0; i < RSS_NENTRIES / 2; ++i) {
		ret = rd_rss_row(adapter, i, &val);
		if (ret)
			return ret;
		*map++ = G_LKPTBLQUEUE0(val);
		*map++ = G_LKPTBLQUEUE1(val);
	}
	return 0;
}