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
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct statfs {int f_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ file_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_READ ; 
 int /*<<< orphan*/  EVFILT_VNODE ; 
 int EV_ADD ; 
 int EV_CLEAR ; 
 int EV_ENABLE ; 
 int /*<<< orphan*/  EV_SET (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ Fflag ; 
 int MNT_LOCAL ; 
 int NOTE_DELETE ; 
 int NOTE_RENAME ; 
 scalar_t__ STDIN_FILENO ; 
 int /*<<< orphan*/  USE_KQUEUE ; 
 int /*<<< orphan*/  USE_SLEEP ; 
 int /*<<< orphan*/  action ; 
 int /*<<< orphan*/ * ev ; 
 scalar_t__ fileno (int /*<<< orphan*/ ) ; 
 scalar_t__ fstatfs (scalar_t__,struct statfs*) ; 
 scalar_t__ kevent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  kq ; 
 int no_files ; 

__attribute__((used)) static void
set_events(file_info_t *files)
{
	int i, n = 0;
	file_info_t *file;
	struct timespec ts;
	struct statfs sf;

	ts.tv_sec = 0;
	ts.tv_nsec = 0;

	action = USE_KQUEUE;
	for (i = 0, file = files; i < no_files; i++, file++) {
		if (! file->fp)
			continue;

		if (fstatfs(fileno(file->fp), &sf) == 0 &&
		    (sf.f_flags & MNT_LOCAL) == 0) {
			action = USE_SLEEP;
			return;
		}

		if (Fflag && fileno(file->fp) != STDIN_FILENO) {
			EV_SET(&ev[n], fileno(file->fp), EVFILT_VNODE,
			    EV_ADD | EV_ENABLE | EV_CLEAR,
			    NOTE_DELETE | NOTE_RENAME, 0, 0);
			n++;
		}
		EV_SET(&ev[n], fileno(file->fp), EVFILT_READ,
		    EV_ADD | EV_ENABLE | EV_CLEAR, 0, 0, 0);
		n++;
	}

	if (kevent(kq, ev, n, NULL, 0, &ts) < 0) {
		action = USE_SLEEP;
	}
}