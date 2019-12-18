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
struct fd_data {int /*<<< orphan*/  fd_bq; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  FD_EMPTY ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  bioq_init (int /*<<< orphan*/ *) ; 
 struct fd_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd_attach2 ; 
 int /*<<< orphan*/  g_post_event (int /*<<< orphan*/ ,struct fd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fd_attach(device_t dev)
{
	struct	fd_data *fd;

	fd = device_get_softc(dev);
	g_post_event(fd_attach2, fd, M_WAITOK, NULL);
	fd->flags |= FD_EMPTY;
	bioq_init(&fd->fd_bq);

	return (0);
}