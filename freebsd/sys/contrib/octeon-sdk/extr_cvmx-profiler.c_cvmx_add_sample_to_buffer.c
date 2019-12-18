#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int core; int /*<<< orphan*/  pc; } ;
typedef  TYPE_3__ cvmx_sample_entry_t ;
struct TYPE_8__ {scalar_t__ head; scalar_t__ end; scalar_t__ data; int /*<<< orphan*/  sample_count; } ;
struct TYPE_10__ {scalar_t__ pcpu_data; TYPE_2__ pcpu_blk_info; } ;
typedef  TYPE_4__ cvmx_ringbuf_t ;
struct TYPE_7__ {scalar_t__* pcpu_base_addr; } ;
struct TYPE_12__ {TYPE_1__ cfg_blk; } ;
struct TYPE_11__ {int /*<<< orphan*/  sample_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  COP0_EPC ; 
 int /*<<< orphan*/  CVMX_MF_COP0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVENT_PERCPU_BUFFER_SIZE ; 
 int /*<<< orphan*/  PRINTF (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_atomic_add64 (int /*<<< orphan*/ *,int) ; 
 int cvmx_get_core_num () ; 
 int /*<<< orphan*/  cvmx_init_pcpu_block (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_read_config_blk () ; 
 scalar_t__ cvmx_unlikely (int) ; 
 TYPE_6__ eccb ; 
 TYPE_5__* pcpu_cfg_blk ; 

__attribute__((used)) static
void cvmx_add_sample_to_buffer(void)
{
    uint32_t epc;
    int cpu = cvmx_get_core_num();
    CVMX_MF_COP0(epc, COP0_EPC);

    cvmx_ringbuf_t  *cpu_buf = (cvmx_ringbuf_t *) eccb.cfg_blk.pcpu_base_addr[cpu];

    /* 
     * head/tail pointer can be NULL, and this case arises when oct-remote-profile is
     * invoked afresh. To keep memory sane for current instance, we clear namedblock off 
     * previous data and this is accomplished by octeon_remote_write_mem from host.
     */
    if (cvmx_unlikely(!cpu_buf->pcpu_blk_info.head && !cpu_buf->pcpu_blk_info.end)) {
       /* Reread the event count as a different threshold val could be 
        * passed with profiler alongside --events flag */
        cvmx_read_config_blk();
        cvmx_init_pcpu_block(cpu, EVENT_PERCPU_BUFFER_SIZE);
    }

    /* In case of hitting end of buffer, reset head,data ptr to start */
    if (cpu_buf->pcpu_blk_info.head == cpu_buf->pcpu_blk_info.end)
        cpu_buf->pcpu_blk_info.head = cpu_buf->pcpu_blk_info.data = cpu_buf->pcpu_data; 

    /* Store the pc, respective core no.*/
    cvmx_sample_entry_t *sample = (cvmx_sample_entry_t *) cpu_buf->pcpu_blk_info.data;
    sample->pc = epc;
    sample->core = cpu;
  
    /* Update Per CPU stats */
    cpu_buf->pcpu_blk_info.sample_count++;
    cpu_buf->pcpu_blk_info.data += sizeof(cvmx_sample_entry_t);
    cpu_buf->pcpu_blk_info.head = cpu_buf->pcpu_blk_info.data;

    /* Increment the global sample count i.e sum total of samples on all cores*/
    cvmx_atomic_add64(&(pcpu_cfg_blk->sample_count), 1);

    PRINTF("the core%d:pc 0x%016lx, sample_count=%ld\n", cpu, sample->pc, cpu_buf->pcpu_blk_info.sample_count);
}