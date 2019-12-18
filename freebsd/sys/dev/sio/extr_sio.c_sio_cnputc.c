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
struct siocnstate {int dummy; } ;
struct consdev {scalar_t__ cn_unit; } ;
typedef  int /*<<< orphan*/  speed_t ;
typedef  scalar_t__ Port_t ;

/* Variables and functions */
 scalar_t__ com_data ; 
 int /*<<< orphan*/  comdefaultrate ; 
 int /*<<< orphan*/  gdbdefaultrate ; 
 int /*<<< orphan*/  kdb_active ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_owned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (scalar_t__,int) ; 
 int sio_inited ; 
 int /*<<< orphan*/  sio_lock ; 
 int /*<<< orphan*/  siocnclose (struct siocnstate*,scalar_t__) ; 
 scalar_t__ siocniobase ; 
 int /*<<< orphan*/  siocnopen (struct siocnstate*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siocntxwait (scalar_t__) ; 
 scalar_t__ siocnunit ; 
 scalar_t__ siogdbiobase ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static void
sio_cnputc(struct consdev *cd, int c)
{
	int	need_unlock;
	int	s;
	struct siocnstate	sp;
	Port_t	iobase;
	speed_t	speed;

	if (cd != NULL && cd->cn_unit == siocnunit) {
		iobase = siocniobase;
		speed = comdefaultrate;
	} else {
#ifdef GDB
		iobase = siogdbiobase;
		speed = gdbdefaultrate;
#else
		return;
#endif
	}
	s = spltty();
	need_unlock = 0;
	if (!kdb_active && sio_inited == 2 && !mtx_owned(&sio_lock)) {
		mtx_lock_spin(&sio_lock);
		need_unlock = 1;
	}
	siocnopen(&sp, iobase, speed);
	siocntxwait(iobase);
	outb(iobase + com_data, c);
	siocnclose(&sp, iobase);
	if (need_unlock)
		mtx_unlock_spin(&sio_lock);
	splx(s);
}