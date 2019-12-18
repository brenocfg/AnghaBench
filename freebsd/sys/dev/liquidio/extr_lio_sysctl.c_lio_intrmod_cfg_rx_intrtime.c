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
typedef  int uint64_t ;
typedef  void* uint32_t ;
struct octeon_intrmod_cfg {int rx_frames; void* rx_usecs; } ;
struct TYPE_2__ {int pf_srn; } ;
struct octeon_device {int chip_id; int num_oqs; void* rx_coalesce_usecs; TYPE_1__ sriov_info; } ;
struct lio {struct octeon_device* oct_dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  LIO_CN23XX_PF_VID 128 
 int /*<<< orphan*/  LIO_CN23XX_SLI_OQ_PKT_INT_LEVELS (int) ; 
 int lio_cn23xx_pf_get_oq_ticks (struct octeon_device*,void*) ; 
 int /*<<< orphan*/  lio_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lio_intrmod_cfg_rx_intrtime(struct lio *lio, struct octeon_intrmod_cfg *intrmod,
			    uint32_t rx_usecs)
{
	struct octeon_device	*oct = lio->oct_dev;
	uint32_t		rx_coalesce_usecs;

	/* Config Time based interrupt values */
	switch (oct->chip_id) {
	case LIO_CN23XX_PF_VID:{
			uint64_t	time_threshold;
			int	q_no;

			if (!rx_usecs)
				rx_coalesce_usecs = intrmod->rx_usecs;
			else
				rx_coalesce_usecs = rx_usecs;

			time_threshold =
			    lio_cn23xx_pf_get_oq_ticks(oct, rx_coalesce_usecs);
			for (q_no = 0; q_no < oct->num_oqs; q_no++) {
				q_no += oct->sriov_info.pf_srn;
				lio_write_csr64(oct,
				       LIO_CN23XX_SLI_OQ_PKT_INT_LEVELS(q_no),
						(intrmod->rx_frames |
					   ((uint64_t)time_threshold << 32)));
				/* consider writing to resend bit here */
			}

			intrmod->rx_usecs = rx_coalesce_usecs;
			oct->rx_coalesce_usecs = rx_coalesce_usecs;
			break;
		}
	default:
		return (EINVAL);
	}

	return (0);
}