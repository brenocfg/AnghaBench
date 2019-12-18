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
typedef  scalar_t__ u_int8_t ;
struct mly_softc {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  operation_device; } ;
struct TYPE_4__ {TYPE_1__ deviceoperation; } ;
struct mly_command_ioctl {TYPE_2__ param; int /*<<< orphan*/  sub_ioctl; } ;
typedef  int /*<<< orphan*/  mci ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MDACIOCTL_FLUSHDEVICEDATA ; 
 int /*<<< orphan*/  MLY_OPDEVICE_PHYSICAL_CONTROLLER ; 
 int /*<<< orphan*/  bzero (struct mly_command_ioctl*,int) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int mly_ioctl (struct mly_softc*,struct mly_command_ioctl*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mly_flush(struct mly_softc *sc)
{
    struct mly_command_ioctl	mci;
    u_int8_t			status;
    int				error;

    debug_called(1);

    /* build the ioctl */
    bzero(&mci, sizeof(mci));
    mci.sub_ioctl = MDACIOCTL_FLUSHDEVICEDATA;
    mci.param.deviceoperation.operation_device = MLY_OPDEVICE_PHYSICAL_CONTROLLER;

    /* pass it off to the controller */
    if ((error = mly_ioctl(sc, &mci, NULL, 0, &status, NULL, NULL)))
	return(error);

    return((status == 0) ? 0 : EIO);
}