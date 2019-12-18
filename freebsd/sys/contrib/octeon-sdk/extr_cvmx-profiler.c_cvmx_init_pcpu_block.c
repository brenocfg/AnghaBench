#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cvmx_sample_entry_t ;
struct TYPE_7__ {int size; int max_samples; char* data; char* head; char* tail; char* end; scalar_t__ sample_read; scalar_t__ sample_count; } ;
struct TYPE_9__ {char* pcpu_data; TYPE_1__ pcpu_blk_info; } ;
typedef  TYPE_3__ cvmx_ringbuf_t ;
typedef  int /*<<< orphan*/  cvmx_cpu_event_block_t ;
struct TYPE_10__ {char** pcpu_base_addr; } ;
typedef  TYPE_4__ cvmx_config_block_t ;
struct TYPE_8__ {char** pcpu_base_addr; } ;
struct TYPE_11__ {TYPE_2__ cfg_blk; scalar_t__ config_blk_base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_BUFFER_BLOCK ; 
 int PADBYTES ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_atomic_set32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_get_memory_addr (int /*<<< orphan*/ ) ; 
 TYPE_6__ eccb ; 
 TYPE_4__* pcpu_cfg_blk ; 
 int /*<<< orphan*/  read_percpu_block ; 

__attribute__((used)) static
void cvmx_init_pcpu_block(int cpu, int size)
{
    eccb.cfg_blk.pcpu_base_addr[cpu] = (char *)cvmx_get_memory_addr(EVENT_BUFFER_BLOCK) + (size * cpu); 
    assert (eccb.cfg_blk.pcpu_base_addr[cpu] != NULL);

    cvmx_ringbuf_t  *cpu_buf = (cvmx_ringbuf_t *) eccb.cfg_blk.pcpu_base_addr[cpu];

    cpu_buf->pcpu_blk_info.size = size;
    cpu_buf->pcpu_blk_info.max_samples = ((size - sizeof(cvmx_cpu_event_block_t)) / sizeof(cvmx_sample_entry_t));
    cpu_buf->pcpu_blk_info.sample_count = 0;
    cpu_buf->pcpu_blk_info.sample_read = 0;
    cpu_buf->pcpu_blk_info.data = eccb.cfg_blk.pcpu_base_addr[cpu] + sizeof(cvmx_cpu_event_block_t) + PADBYTES;
    cpu_buf->pcpu_blk_info.head = cpu_buf->pcpu_blk_info.tail = \
       cpu_buf->pcpu_data = cpu_buf->pcpu_blk_info.data;
    cpu_buf->pcpu_blk_info.end = eccb.cfg_blk.pcpu_base_addr[cpu] + size;

    cvmx_atomic_set32(&read_percpu_block, 0);

    /*
     * Write per cpu mem base address info in to 'event config' named block,
     * This info is needed by oct-remote-profile to get Per cpu memory 
     * base address of each core of the named block.
     */
    pcpu_cfg_blk = (cvmx_config_block_t *) eccb.config_blk_base_addr;
    pcpu_cfg_blk->pcpu_base_addr[cpu] = eccb.cfg_blk.pcpu_base_addr[cpu];
}