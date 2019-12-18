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
struct octeon_intrmod_cfg {int dummy; } ;
struct octeon_device {int dummy; } ;
struct lio_soft_command {int wait_time; struct lio_soft_command* callback_arg; int /*<<< orphan*/  callback; int /*<<< orphan*/  iq_no; scalar_t__ virtrptr; } ;
struct lio_intrmod_resp {int dummy; } ;
struct TYPE_6__ {TYPE_2__* txpciq; } ;
struct lio {TYPE_3__ linfo; struct octeon_device* oct_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_5__ {TYPE_1__ s; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int LIO_IQ_SEND_FAILED ; 
 int /*<<< orphan*/  LIO_OPCODE_NIC ; 
 int /*<<< orphan*/  LIO_OPCODE_NIC_INTRMOD_PARAMS ; 
 int /*<<< orphan*/  bzero (struct lio_intrmod_resp*,int) ; 
 struct lio_soft_command* lio_alloc_soft_command (struct octeon_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_free_soft_command (struct octeon_device*,struct lio_soft_command*) ; 
 int /*<<< orphan*/  lio_get_intrmod_callback ; 
 int /*<<< orphan*/  lio_prepare_soft_command (struct octeon_device*,struct lio_soft_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lio_send_soft_command (struct octeon_device*,struct lio_soft_command*) ; 

__attribute__((used)) static int
lio_get_intrmod_cfg(struct lio *lio, struct octeon_intrmod_cfg *intr_cfg)
{
	struct lio_soft_command	*sc;
	struct lio_intrmod_resp	*resp;
	struct octeon_device	*oct_dev = lio->oct_dev;
	int	retval;

	/* Alloc soft command */
	sc = lio_alloc_soft_command(oct_dev, 0, sizeof(struct lio_intrmod_resp),
				    0);

	if (sc == NULL)
		return (ENOMEM);

	resp = (struct lio_intrmod_resp *)sc->virtrptr;
	bzero(resp, sizeof(struct lio_intrmod_resp));
	sc->iq_no = lio->linfo.txpciq[0].s.q_no;

	lio_prepare_soft_command(oct_dev, sc, LIO_OPCODE_NIC,
				 LIO_OPCODE_NIC_INTRMOD_PARAMS, 0, 0, 0);

	sc->callback = lio_get_intrmod_callback;
	sc->callback_arg = sc;
	sc->wait_time = 1000;

	retval = lio_send_soft_command(oct_dev, sc);
	if (retval == LIO_IQ_SEND_FAILED) {
		lio_free_soft_command(oct_dev, sc);
		return (EINVAL);
	}

	return (0);
}