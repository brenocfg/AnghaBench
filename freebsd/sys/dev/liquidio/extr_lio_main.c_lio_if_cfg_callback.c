#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  lio_firmware_version; } ;
struct octeon_device {TYPE_1__ fw_info; } ;
struct lio_soft_command {scalar_t__ ctxptr; scalar_t__ virtrptr; } ;
struct TYPE_4__ {char* lio_firmware_version; } ;
struct lio_if_cfg_resp {TYPE_2__ cfg_info; scalar_t__ status; } ;
struct lio_if_cfg_context {int cond; int /*<<< orphan*/  octeon_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIO_CAST64 (scalar_t__) ; 
 int /*<<< orphan*/  lio_dev_err (struct octeon_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct octeon_device* lio_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
lio_if_cfg_callback(struct octeon_device *oct, uint32_t status, void *buf)
{
	struct lio_soft_command	*sc = (struct lio_soft_command *)buf;
	struct lio_if_cfg_resp	*resp;
	struct lio_if_cfg_context *ctx;

	resp = (struct lio_if_cfg_resp *)sc->virtrptr;
	ctx = (struct lio_if_cfg_context *)sc->ctxptr;

	oct = lio_get_device(ctx->octeon_id);
	if (resp->status)
		lio_dev_err(oct, "nic if cfg instruction failed. Status: %llx (0x%08x)\n",
			    LIO_CAST64(resp->status), status);
	ctx->cond = 1;

	snprintf(oct->fw_info.lio_firmware_version, 32, "%s",
		 resp->cfg_info.lio_firmware_version);

	/*
	 * This barrier is required to be sure that the response has been
	 * written fully before waking up the handler
	 */
	wmb();
}