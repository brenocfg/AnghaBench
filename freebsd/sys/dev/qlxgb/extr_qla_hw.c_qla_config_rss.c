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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  qla_host_t ;
struct TYPE_5__ {int /*<<< orphan*/  cntxt_id; int /*<<< orphan*/  opcode; int /*<<< orphan*/  cmd; } ;
struct TYPE_6__ {int hash_type; int ind_tbl_mask; int /*<<< orphan*/ * rss_key; int /*<<< orphan*/  flags; TYPE_1__ hdr; } ;
typedef  TYPE_2__ qla_fw_cds_config_rss_t ;

/* Variables and functions */
 int /*<<< orphan*/  Q8_FWCD_CNTRL_REQ ; 
 int /*<<< orphan*/  Q8_FWCD_OPCODE_CONFIG_RSS ; 
 int /*<<< orphan*/  Q8_FWCD_RSS_FLAGS_ENABLE_RSS ; 
 int Q8_FWCD_RSS_HASH_TYPE_IPV4_TCP_IP ; 
 int Q8_FWCD_RSS_HASH_TYPE_IPV6_TCP_IP ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int qla_fw_cmd (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/ * rss_key ; 

__attribute__((used)) static int
qla_config_rss(qla_host_t *ha, uint16_t cntxt_id)
{
	qla_fw_cds_config_rss_t rss_config;
	int ret, i;

	bzero(&rss_config, sizeof(qla_fw_cds_config_rss_t));

	rss_config.hdr.cmd = Q8_FWCD_CNTRL_REQ;
	rss_config.hdr.opcode = Q8_FWCD_OPCODE_CONFIG_RSS;
	rss_config.hdr.cntxt_id = cntxt_id;

	rss_config.hash_type = (Q8_FWCD_RSS_HASH_TYPE_IPV4_TCP_IP |
					Q8_FWCD_RSS_HASH_TYPE_IPV6_TCP_IP);
	rss_config.flags = Q8_FWCD_RSS_FLAGS_ENABLE_RSS;

	rss_config.ind_tbl_mask = 0x7;
	
	for (i = 0; i < 5; i++)
		rss_config.rss_key[i] = rss_key[i];

	ret = qla_fw_cmd(ha, &rss_config, sizeof(qla_fw_cds_config_rss_t));

	return ret;
}