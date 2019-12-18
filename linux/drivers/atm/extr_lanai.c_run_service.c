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
typedef  int u32 ;
struct TYPE_2__ {int* start; int const* ptr; int const* end; } ;
struct lanai_dev {int /*<<< orphan*/  transmit_ready; TYPE_1__ service; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUM_VCI ; 
 int /*<<< orphan*/  ServRead_Reg ; 
 int /*<<< orphan*/  ServWrite_Reg ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ handle_service (struct lanai_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iter_transmit ; 
 int /*<<< orphan*/  le32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int reg_read (struct lanai_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct lanai_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcc_sklist_lock ; 
 int /*<<< orphan*/  vci_bitfield_iterate (struct lanai_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void run_service(struct lanai_dev *lanai)
{
	int ntx = 0;
	u32 wreg = reg_read(lanai, ServWrite_Reg);
	const u32 *end = lanai->service.start + wreg;
	while (lanai->service.ptr != end) {
		ntx += handle_service(lanai,
		    le32_to_cpup(lanai->service.ptr++));
		if (lanai->service.ptr >= lanai->service.end)
			lanai->service.ptr = lanai->service.start;
	}
	reg_write(lanai, wreg, ServRead_Reg);
	if (ntx != 0) {
		read_lock(&vcc_sklist_lock);
		vci_bitfield_iterate(lanai, lanai->transmit_ready,
		    iter_transmit);
		bitmap_zero(lanai->transmit_ready, NUM_VCI);
		read_unlock(&vcc_sklist_lock);
	}
}