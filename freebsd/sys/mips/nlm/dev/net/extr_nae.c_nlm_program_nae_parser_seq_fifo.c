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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct nae_port_config {int pseq_fifo_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAE_PARSER_SEQ_FIFO_CFG ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
nlm_program_nae_parser_seq_fifo(uint64_t nae_base, int maxports,
    struct nae_port_config *cfg)
{
	uint32_t val;
	int start = 0, size, i;

	for (i = 0; i < maxports; i++) {
		size = cfg[i].pseq_fifo_size;
		val = (((size & 0x1fff) << 17) |
		    ((start & 0xfff) << 5) |
		    (i & 0x1f));
		nlm_write_nae_reg(nae_base, NAE_PARSER_SEQ_FIFO_CFG, val);
		start += size;
	}
}