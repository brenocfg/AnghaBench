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
typedef  int u64 ;

/* Variables and functions */
 int NUM_SPU_BITS_TRBUF ; 
 int SPUS_PER_TB_ENTRY ; 
 int SPU_PC_MASK ; 
 int TRACE_ARRAY_SIZE ; 
 int /*<<< orphan*/  cbe_read_trace_buffer (int,int*) ; 
 int* samples ; 

__attribute__((used)) static void spu_pc_extract(int cpu, int entry)
{
	/* the trace buffer is 128 bits */
	u64 trace_buffer[2];
	u64 spu_mask;
	int spu;

	spu_mask = SPU_PC_MASK;

	/* Each SPU PC is 16 bits; hence, four spus in each of
	 * the two 64-bit buffer entries that make up the
	 * 128-bit trace_buffer entry.	Process two 64-bit values
	 * simultaneously.
	 * trace[0] SPU PC contents are: 0 1 2 3
	 * trace[1] SPU PC contents are: 4 5 6 7
	 */

	cbe_read_trace_buffer(cpu, trace_buffer);

	for (spu = SPUS_PER_TB_ENTRY-1; spu >= 0; spu--) {
		/* spu PC trace entry is upper 16 bits of the
		 * 18 bit SPU program counter
		 */
		samples[spu * TRACE_ARRAY_SIZE + entry]
			= (spu_mask & trace_buffer[0]) << 2;
		samples[(spu + SPUS_PER_TB_ENTRY) * TRACE_ARRAY_SIZE + entry]
			= (spu_mask & trace_buffer[1]) << 2;

		trace_buffer[0] = trace_buffer[0] >> NUM_SPU_BITS_TRBUF;
		trace_buffer[1] = trace_buffer[1] >> NUM_SPU_BITS_TRBUF;
	}
}