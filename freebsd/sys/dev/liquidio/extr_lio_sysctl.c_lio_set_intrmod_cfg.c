#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct octeon_intrmod_cfg {int rx_enable; } ;
struct octeon_device {int dummy; } ;
struct lio_soft_command {int wait_time; struct lio_soft_command* callback_arg; int /*<<< orphan*/  callback; int /*<<< orphan*/  iq_no; scalar_t__ virtdptr; scalar_t__ ctxptr; } ;
struct lio_intrmod_context {int status; scalar_t__ cond; int /*<<< orphan*/  octeon_id; } ;
struct TYPE_6__ {TYPE_2__* txpciq; } ;
struct lio {TYPE_3__ linfo; struct octeon_device* oct_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_5__ {TYPE_1__ s; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  LIO_CAST64 (int) ; 
 int LIO_IQ_SEND_FAILED ; 
 int /*<<< orphan*/  LIO_OPCODE_NIC ; 
 int /*<<< orphan*/  LIO_OPCODE_NIC_INTRMOD_CFG ; 
 struct lio_soft_command* lio_alloc_soft_command (struct octeon_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lio_dev_err (struct octeon_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_dev_info (struct octeon_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_free_soft_command (struct octeon_device*,struct lio_soft_command*) ; 
 int /*<<< orphan*/  lio_get_device_id (struct octeon_device*) ; 
 int /*<<< orphan*/  lio_prepare_soft_command (struct octeon_device*,struct lio_soft_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lio_send_soft_command (struct octeon_device*,struct lio_soft_command*) ; 
 int /*<<< orphan*/  lio_set_intrmod_callback ; 
 int /*<<< orphan*/  lio_sleep_cond (struct octeon_device*,scalar_t__*) ; 
 int /*<<< orphan*/  lio_swap_8B_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (struct octeon_intrmod_cfg*,struct octeon_intrmod_cfg*,int) ; 

__attribute__((used)) static int
lio_set_intrmod_cfg(struct lio *lio, struct octeon_intrmod_cfg *intr_cfg)
{
	struct lio_soft_command		*sc;
	struct lio_intrmod_context	*ctx;
	struct octeon_intrmod_cfg	*cfg;
	struct octeon_device		*oct_dev = lio->oct_dev;
	int	retval;

	/* Alloc soft command */
	sc = lio_alloc_soft_command(oct_dev, sizeof(struct octeon_intrmod_cfg),
				    0, sizeof(struct lio_intrmod_context));

	if (sc == NULL)
		return (ENOMEM);

	ctx = (struct lio_intrmod_context *)sc->ctxptr;

	ctx->cond = 0;
	ctx->octeon_id = lio_get_device_id(oct_dev);

	cfg = (struct octeon_intrmod_cfg *)sc->virtdptr;

	memcpy(cfg, intr_cfg, sizeof(struct octeon_intrmod_cfg));
	lio_swap_8B_data((uint64_t *)cfg,
			 (sizeof(struct octeon_intrmod_cfg)) / 8);

	sc->iq_no = lio->linfo.txpciq[0].s.q_no;

	lio_prepare_soft_command(oct_dev, sc, LIO_OPCODE_NIC,
				 LIO_OPCODE_NIC_INTRMOD_CFG, 0, 0, 0);

	sc->callback = lio_set_intrmod_callback;
	sc->callback_arg = sc;
	sc->wait_time = 1000;

	retval = lio_send_soft_command(oct_dev, sc);
	if (retval == LIO_IQ_SEND_FAILED) {
		lio_free_soft_command(oct_dev, sc);
		return (EINVAL);
	}

	/*
	 * Sleep on a wait queue till the cond flag indicates that the
	 * response arrived or timed-out.
	 */
	lio_sleep_cond(oct_dev, &ctx->cond);

	retval = ctx->status;
	if (retval)
		lio_dev_err(oct_dev, "intrmod config failed. Status: %llx\n",
			    LIO_CAST64(retval));
	else
		lio_dev_info(oct_dev, "Rx-Adaptive Interrupt moderation enabled:%llx\n",
			     LIO_CAST64(intr_cfg->rx_enable));

	lio_free_soft_command(oct_dev, sc);

	return ((retval) ? ETIMEDOUT : 0);
}