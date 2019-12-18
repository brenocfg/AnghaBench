#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sub ;
struct kevent {int flags; int /*<<< orphan*/  fflags; int /*<<< orphan*/  ident; int /*<<< orphan*/  filter; scalar_t__ data; int /*<<< orphan*/  udata; } ;
struct cloudabi64_kevent_args {int /*<<< orphan*/  in; } ;
typedef  scalar_t__ cloudabi_timestamp_t ;
struct TYPE_8__ {int /*<<< orphan*/  fd; } ;
struct TYPE_7__ {int /*<<< orphan*/  fd; } ;
struct TYPE_6__ {int flags; scalar_t__ timeout; int /*<<< orphan*/  clock_id; int /*<<< orphan*/  identifier; } ;
struct TYPE_9__ {int type; TYPE_3__ proc_terminate; TYPE_2__ fd_readwrite; TYPE_1__ clock; int /*<<< orphan*/  userdata; } ;
typedef  TYPE_4__ cloudabi64_subscription_t ;

/* Variables and functions */
#define  CLOUDABI_EVENTTYPE_CLOCK 131 
#define  CLOUDABI_EVENTTYPE_FD_READ 130 
#define  CLOUDABI_EVENTTYPE_FD_WRITE 129 
#define  CLOUDABI_EVENTTYPE_PROC_TERMINATE 128 
 int CLOUDABI_SUBSCRIPTION_CLOCK_ABSTIME ; 
 int /*<<< orphan*/  EVFILT_PROCDESC ; 
 int /*<<< orphan*/  EVFILT_READ ; 
 int /*<<< orphan*/  EVFILT_TIMER ; 
 int /*<<< orphan*/  EVFILT_WRITE ; 
 int EV_ADD ; 
 int EV_ONESHOT ; 
 scalar_t__ INTPTR_MAX ; 
 int /*<<< orphan*/  NOTE_EXIT ; 
 int /*<<< orphan*/  NOTE_FILE_POLL ; 
 int /*<<< orphan*/  NOTE_NSECONDS ; 
 int /*<<< orphan*/  TO_PTR (int /*<<< orphan*/ ) ; 
 int cloudabi_clock_time_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int copyin (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  memset (struct kevent*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
cloudabi64_kevent_copyin(void *arg, struct kevent *kevp, int count)
{
	cloudabi64_subscription_t sub;
	struct cloudabi64_kevent_args *args;
	cloudabi_timestamp_t ts;
	int error;

	args = arg;
	while (count-- > 0) {
		/* TODO(ed): Copy in multiple entries at once. */
		error = copyin(args->in++, &sub, sizeof(sub));
		if (error != 0)
			return (error);

		memset(kevp, 0, sizeof(*kevp));
		kevp->udata = TO_PTR(sub.userdata);
		switch (sub.type) {
		case CLOUDABI_EVENTTYPE_CLOCK:
			kevp->filter = EVFILT_TIMER;
			kevp->ident = sub.clock.identifier;
			kevp->fflags = NOTE_NSECONDS;
			if ((sub.clock.flags &
			    CLOUDABI_SUBSCRIPTION_CLOCK_ABSTIME) != 0 &&
			    sub.clock.timeout > 0) {
				/* Convert absolute timestamp to a relative. */
				error = cloudabi_clock_time_get(curthread,
				    sub.clock.clock_id, &ts);
				if (error != 0)
					return (error);
				ts = ts > sub.clock.timeout ? 0 :
				    sub.clock.timeout - ts;
			} else {
				/* Relative timestamp. */
				ts = sub.clock.timeout;
			}
			kevp->data = ts > INTPTR_MAX ? INTPTR_MAX : ts;
			break;
		case CLOUDABI_EVENTTYPE_FD_READ:
			kevp->filter = EVFILT_READ;
			kevp->ident = sub.fd_readwrite.fd;
			kevp->fflags = NOTE_FILE_POLL;
			break;
		case CLOUDABI_EVENTTYPE_FD_WRITE:
			kevp->filter = EVFILT_WRITE;
			kevp->ident = sub.fd_readwrite.fd;
			break;
		case CLOUDABI_EVENTTYPE_PROC_TERMINATE:
			kevp->filter = EVFILT_PROCDESC;
			kevp->ident = sub.proc_terminate.fd;
			kevp->fflags = NOTE_EXIT;
			break;
		}
		kevp->flags = EV_ADD | EV_ONESHOT;
		++kevp;
	}
	return (0);
}