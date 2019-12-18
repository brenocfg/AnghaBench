#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  cpu_clock_hz; void* board_rev_minor; void* board_rev_major; int /*<<< orphan*/  board_type; int /*<<< orphan*/  phy_mem_desc_addr; } ;
struct TYPE_3__ {TYPE_2__ sysinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 
 TYPE_1__ state ; 

int cvmx_sysinfo_minimal_initialize(uint64_t phy_mem_desc_addr, uint16_t board_type, uint8_t board_rev_major,
                                    uint8_t board_rev_minor, uint32_t cpu_clock_hz)
{


    memset(&(state.sysinfo), 0x0, sizeof(state.sysinfo));
    state.sysinfo.phy_mem_desc_addr = phy_mem_desc_addr;
    state.sysinfo.board_type = board_type;
    state.sysinfo.board_rev_major = board_rev_major;
    state.sysinfo.board_rev_minor = board_rev_minor;
    state.sysinfo.cpu_clock_hz = cpu_clock_hz;

    return(1);
}