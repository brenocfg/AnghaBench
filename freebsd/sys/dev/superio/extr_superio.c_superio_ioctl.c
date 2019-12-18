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
typedef  int u_long ;
struct thread {int dummy; } ;
struct superiocmd {int /*<<< orphan*/  val; int /*<<< orphan*/  cr; int /*<<< orphan*/  ldn; } ;
struct siosc {int dummy; } ;
struct cdev {struct siosc* si_drv1; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int ENOTTY ; 
#define  SUPERIO_CR_READ 129 
#define  SUPERIO_CR_WRITE 128 
 int /*<<< orphan*/  sio_conf_enter (struct siosc*) ; 
 int /*<<< orphan*/  sio_conf_exit (struct siosc*) ; 
 int /*<<< orphan*/  sio_ldn_read (struct siosc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sio_ldn_write (struct siosc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
superio_ioctl(struct cdev *dev, u_long cmd, caddr_t data, int flags,
    struct thread *td)
{
	struct siosc *sc;
	struct superiocmd *s;

	sc = dev->si_drv1;
	s = (struct superiocmd *)data;
	switch (cmd) {
	case SUPERIO_CR_READ:
		sio_conf_enter(sc);
		s->val = sio_ldn_read(sc, s->ldn, s->cr);
		sio_conf_exit(sc);
		return (0);
	case SUPERIO_CR_WRITE:
		sio_conf_enter(sc);
		sio_ldn_write(sc, s->ldn, s->cr, s->val);
		sio_conf_exit(sc);
		return (0);
	default:
		return (ENOTTY);
	}
}