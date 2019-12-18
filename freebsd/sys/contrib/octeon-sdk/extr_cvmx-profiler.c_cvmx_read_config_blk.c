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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_3__ {int /*<<< orphan*/  sample_count; int /*<<< orphan*/  events; } ;
struct TYPE_4__ {char* config_blk_base_addr; TYPE_1__ cfg_blk; int /*<<< orphan*/  read_cfg_blk; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_BUFFER_CONFIG_BLOCK ; 
 int /*<<< orphan*/  PRINTF (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_atomic_set32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cvmx_config_block_t ; 
 scalar_t__ cvmx_get_memory_addr (int /*<<< orphan*/ ) ; 
 TYPE_2__ eccb ; 
 int /*<<< orphan*/  events ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void cvmx_read_config_blk(void)
{
    eccb.config_blk_base_addr = (char *)cvmx_get_memory_addr(EVENT_BUFFER_CONFIG_BLOCK);
    memcpy(&(eccb.cfg_blk.events), eccb.config_blk_base_addr + \
       offsetof(cvmx_config_block_t, events), sizeof(int64_t));

    cvmx_atomic_set32(&eccb.read_cfg_blk,1);
    PRINTF("cfg_blk.events=%lu, sample_count=%ld\n", eccb.cfg_blk.events, eccb.cfg_blk.sample_count);
}