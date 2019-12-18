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
typedef  scalar_t__ uint8_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  qla_host_t ;

/* Variables and functions */
 size_t Q81_ADDRESS_REGISTER_ENABLE ; 
 int /*<<< orphan*/  Q81_CTL_XG_PROBE_MUX_ADDR ; 
 int /*<<< orphan*/  Q81_CTL_XG_PROBE_MUX_DATA ; 
 size_t Q81_MAX_MODULES ; 
 size_t Q81_MAX_MUX ; 
 size_t Q81_UP ; 
 size_t READ_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static uint32_t *
qls_get_probe(qla_host_t *ha, uint32_t clock, uint8_t *valid, uint32_t *buf)
{
	uint32_t module, mux_sel, probe, lo_val, hi_val;

	for (module = 0; module < Q81_MAX_MODULES; module ++) {

		if (valid[module]) {

			for (mux_sel = 0; mux_sel < Q81_MAX_MUX; mux_sel++) {

				probe = clock | Q81_ADDRESS_REGISTER_ENABLE |
						mux_sel | (module << 9);
				WRITE_REG32(ha, Q81_CTL_XG_PROBE_MUX_ADDR,\
					probe);

				lo_val = READ_REG32(ha,\
						Q81_CTL_XG_PROBE_MUX_DATA);

				if (mux_sel == 0) {
					*buf = probe;
					buf ++;
				}

				probe |= Q81_UP;

				WRITE_REG32(ha, Q81_CTL_XG_PROBE_MUX_ADDR,\
					probe);
				hi_val = READ_REG32(ha,\
						Q81_CTL_XG_PROBE_MUX_DATA);

				*buf = lo_val;
				buf++;
				*buf = hi_val;
				buf++;
			}
		}
	}

	return(buf);
}