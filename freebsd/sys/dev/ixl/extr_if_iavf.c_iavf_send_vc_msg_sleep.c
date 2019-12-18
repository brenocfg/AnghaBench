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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  ctx; } ;
struct iavf_sc {int /*<<< orphan*/  dev; TYPE_1__ vsi; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  IAVF_AQ_TIMEOUT ; 
 int /*<<< orphan*/  IAVF_FLAGS ; 
 int /*<<< orphan*/  PRI_MAX ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iavf_dbg_vc (struct iavf_sc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  iflib_ctx_lock_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_in_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_vc_get_op_chan (struct iavf_sc*,int /*<<< orphan*/ ) ; 
 int ixl_vc_send_cmd (struct iavf_sc*,int /*<<< orphan*/ ) ; 
 int sx_sleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iavf_send_vc_msg_sleep(struct iavf_sc *sc, u32 op)
{
	int error = 0;
	if_ctx_t ctx = sc->vsi.ctx;

	error = ixl_vc_send_cmd(sc, op);
	if (error != 0) {
		iavf_dbg_vc(sc, "Error sending %b: %d\n", op, IAVF_FLAGS, error);
		return (error);
	}

	/* Don't wait for a response if the device is being detached. */
	if (!iflib_in_detach(ctx)) {
		iavf_dbg_vc(sc, "Sleeping for op %b\n", op, IAVF_FLAGS);
		error = sx_sleep(ixl_vc_get_op_chan(sc, op),
		    iflib_ctx_lock_get(ctx), PRI_MAX, "iavf_vc", IAVF_AQ_TIMEOUT);

		if (error == EWOULDBLOCK)
			device_printf(sc->dev, "%b timed out\n", op, IAVF_FLAGS);
	}

	return (error);
}