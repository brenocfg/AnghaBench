#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mxge_softc_t ;
struct TYPE_3__ {scalar_t__ data0; } ;
typedef  TYPE_1__ mxge_cmd_t ;

/* Variables and functions */
 scalar_t__ MJUMPAGESIZE ; 
 int /*<<< orphan*/  MXGEFW_CMD_ALWAYS_USE_N_BIG_BUFFERS ; 
 scalar_t__ MXGEFW_MAX_MTU ; 
 scalar_t__ MXGEFW_PAD ; 
 int mxge_send_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
mxge_max_mtu(mxge_softc_t *sc)
{
	mxge_cmd_t cmd;
	int status;

	if (MJUMPAGESIZE - MXGEFW_PAD >  MXGEFW_MAX_MTU)
		return  MXGEFW_MAX_MTU - MXGEFW_PAD;

	/* try to set nbufs to see if it we can
	   use virtually contiguous jumbos */
	cmd.data0 = 0;
	status = mxge_send_cmd(sc, MXGEFW_CMD_ALWAYS_USE_N_BIG_BUFFERS,
			       &cmd);
	if (status == 0)
		return  MXGEFW_MAX_MTU - MXGEFW_PAD;

	/* otherwise, we're limited to MJUMPAGESIZE */
	return MJUMPAGESIZE - MXGEFW_PAD;
}