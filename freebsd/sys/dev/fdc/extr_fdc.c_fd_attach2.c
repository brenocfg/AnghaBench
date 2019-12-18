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
struct fd_data {int /*<<< orphan*/  fd_provider; TYPE_1__* fd_geom; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct fd_data* softc; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_error_provider (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_fd_class ; 
 TYPE_1__* g_new_geomf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_new_providerf (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fd_attach2(void *arg, int flag)
{
	struct	fd_data *fd;

	fd = arg;

	fd->fd_geom = g_new_geomf(&g_fd_class,
	    "fd%d", device_get_unit(fd->dev));
	fd->fd_provider = g_new_providerf(fd->fd_geom, "%s", fd->fd_geom->name);
	fd->fd_geom->softc = fd;
	g_error_provider(fd->fd_provider, 0);
}