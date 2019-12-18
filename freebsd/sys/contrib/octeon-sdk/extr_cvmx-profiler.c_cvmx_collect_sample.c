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
struct TYPE_3__ {int /*<<< orphan*/  events; } ;
struct TYPE_4__ {TYPE_1__ cfg_blk; int /*<<< orphan*/  read_cfg_blk; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_PERCPU_BUFFER_SIZE ; 
 int /*<<< orphan*/  cvmx_add_sample_to_buffer () ; 
 int /*<<< orphan*/  cvmx_get_core_num () ; 
 int /*<<< orphan*/  cvmx_init_pcpu_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_read_config_blk () ; 
 int /*<<< orphan*/  cvmx_reset_perf_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ eccb ; 
 scalar_t__ read_percpu_block ; 

void cvmx_collect_sample(void)
{
    if (!eccb.read_cfg_blk)
        cvmx_read_config_blk();

    if (read_percpu_block)
        cvmx_init_pcpu_block(cvmx_get_core_num(), EVENT_PERCPU_BUFFER_SIZE);

    cvmx_add_sample_to_buffer();
    cvmx_reset_perf_counter(0, eccb.cfg_blk.events);
}