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
struct ccp_cmd_queue {long total_ops; long total_aes_ops; long total_xts_aes_ops; long total_3des_ops; long total_sha_ops; long total_rsa_ops; long total_pt_ops; long total_ecc_ops; } ;

/* Variables and functions */

__attribute__((used)) static void ccp5_debugfs_reset_queue_stats(struct ccp_cmd_queue *cmd_q)
{
	cmd_q->total_ops = 0L;
	cmd_q->total_aes_ops = 0L;
	cmd_q->total_xts_aes_ops = 0L;
	cmd_q->total_3des_ops = 0L;
	cmd_q->total_sha_ops = 0L;
	cmd_q->total_rsa_ops = 0L;
	cmd_q->total_pt_ops = 0L;
	cmd_q->total_ecc_ops = 0L;
}