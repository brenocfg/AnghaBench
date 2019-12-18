#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct si_sm_data {int write_count; int /*<<< orphan*/ * write_data; int /*<<< orphan*/  seq; TYPE_1__* io; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BT_DEBUG_MSG ; 
 int /*<<< orphan*/  HOST2BMC (int /*<<< orphan*/ ) ; 
 int bt_debug ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 

__attribute__((used)) static inline void write_all_bytes(struct si_sm_data *bt)
{
	int i;

	if (bt_debug & BT_DEBUG_MSG) {
		dev_dbg(bt->io->dev, "write %d bytes seq=0x%02X",
			bt->write_count, bt->seq);
		for (i = 0; i < bt->write_count; i++)
			pr_cont(" %02x", bt->write_data[i]);
		pr_cont("\n");
	}
	for (i = 0; i < bt->write_count; i++)
		HOST2BMC(bt->write_data[i]);
}