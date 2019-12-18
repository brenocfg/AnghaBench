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
struct sbp2_logical_unit {int /*<<< orphan*/  generation; TYPE_1__* tgt; } ;
struct fw_device {int /*<<< orphan*/  max_speed; int /*<<< orphan*/  card; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  node_id; } ;

/* Variables and functions */
 scalar_t__ CSR_BUSY_TIMEOUT ; 
 scalar_t__ CSR_REGISTER_BASE ; 
 int SBP2_CYCLE_LIMIT ; 
 int SBP2_RETRY_LIMIT ; 
 int /*<<< orphan*/  TCODE_WRITE_QUADLET_REQUEST ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  fw_run_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 struct fw_device* target_parent_device (TYPE_1__*) ; 

__attribute__((used)) static void sbp2_set_busy_timeout(struct sbp2_logical_unit *lu)
{
	struct fw_device *device = target_parent_device(lu->tgt);
	__be32 d = cpu_to_be32(SBP2_CYCLE_LIMIT | SBP2_RETRY_LIMIT);

	fw_run_transaction(device->card, TCODE_WRITE_QUADLET_REQUEST,
			   lu->tgt->node_id, lu->generation, device->max_speed,
			   CSR_REGISTER_BASE + CSR_BUSY_TIMEOUT, &d, 4);
}