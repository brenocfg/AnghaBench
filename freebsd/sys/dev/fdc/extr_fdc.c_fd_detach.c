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
struct fd_data {int /*<<< orphan*/  toffhandle; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ DS_BUSY ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PZERO ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct fd_data* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd_detach_geom ; 
 int /*<<< orphan*/  g_waitfor_event (int /*<<< orphan*/ ,struct fd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hz ; 
 int /*<<< orphan*/  tsleep (struct fd_data*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
fd_detach(device_t dev)
{
	struct	fd_data *fd;

	fd = device_get_softc(dev);
	g_waitfor_event(fd_detach_geom, fd, M_WAITOK, NULL);
	while (device_get_state(dev) == DS_BUSY)
		tsleep(fd, PZERO, "fdd", hz/10);
	callout_drain(&fd->toffhandle);

	return (0);
}