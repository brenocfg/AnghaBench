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
struct TYPE_2__ {int /*<<< orphan*/  ifp; } ;
struct octeon_device {TYPE_1__ props; } ;
struct lio {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct octeon_device* device_get_softc (int /*<<< orphan*/ ) ; 
 struct lio* if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_send_rx_ctrl_cmd (struct lio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lio_shutdown(device_t dev)
{
	struct octeon_device	*oct_dev = device_get_softc(dev);
	struct lio	*lio = if_getsoftc(oct_dev->props.ifp);

	lio_send_rx_ctrl_cmd(lio, 0);

	return (0);
}