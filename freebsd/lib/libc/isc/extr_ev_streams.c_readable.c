#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; int ioDone; int ioTotal; scalar_t__ ioErrno; int /*<<< orphan*/  timer; int /*<<< orphan*/  iovCurCount; int /*<<< orphan*/  iovCur; } ;
typedef  TYPE_1__ evStream ;
typedef  int /*<<< orphan*/  evContext ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int EV_STR_TIMEROK ; 
 int /*<<< orphan*/  UNUSED (int) ; 
 int /*<<< orphan*/  consume (TYPE_1__*,int) ; 
 int /*<<< orphan*/  done (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  evTouchIdleTimer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readv (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
readable(evContext opaqueCtx, void *uap, int fd, int evmask) {
	evStream *str = uap;
	int bytes;

	UNUSED(evmask);

	bytes = readv(fd, str->iovCur, str->iovCurCount);
	if (bytes > 0) {
		if ((str->flags & EV_STR_TIMEROK) != 0)
			evTouchIdleTimer(opaqueCtx, str->timer);
		consume(str, bytes);
	} else {
		if (bytes == 0)
			str->ioDone = 0;
		else {
			if (errno != EINTR) {
				str->ioDone = -1;
				str->ioErrno = errno;
			}
		}
	}
	if (str->ioDone <= 0 || str->ioDone == str->ioTotal)
		done(opaqueCtx, str);
}