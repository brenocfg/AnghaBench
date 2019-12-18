#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_5__ {int num_sds_rings; int /*<<< orphan*/  rcv_cntxt_id; } ;
struct TYPE_6__ {TYPE_1__ hw; } ;
typedef  TYPE_2__ qla_host_t ;

/* Variables and functions */
 int Q8_CONFIG_IND_TBL_SIZE ; 
 int Q8_RSS_IND_TBL_MAX_IDX ; 
 scalar_t__ qla_set_rss_ind_table (TYPE_2__*,int,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
qla_config_rss_ind_table(qla_host_t *ha)
{
	uint32_t i, count;
	uint8_t rss_ind_tbl[Q8_CONFIG_IND_TBL_SIZE];


	for (i = 0; i < Q8_CONFIG_IND_TBL_SIZE; i++) {
		rss_ind_tbl[i] = i % ha->hw.num_sds_rings;
	}

	for (i = 0; i <= Q8_RSS_IND_TBL_MAX_IDX ;
		i = i + Q8_CONFIG_IND_TBL_SIZE) {

		if ((i + Q8_CONFIG_IND_TBL_SIZE) > Q8_RSS_IND_TBL_MAX_IDX) {
			count = Q8_RSS_IND_TBL_MAX_IDX - i + 1;
		} else {
			count = Q8_CONFIG_IND_TBL_SIZE;
		}

		if (qla_set_rss_ind_table(ha, i, count, ha->hw.rcv_cntxt_id,
			rss_ind_tbl))
			return (-1);
	}

	return (0);
}