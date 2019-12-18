#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  we_cv; struct thread* we_td; } ;
typedef  TYPE_1__ wb_ext ;
struct TYPE_9__ {int wb_waittype; int wb_waitkey; scalar_t__ wb_awakened; int /*<<< orphan*/  wb_waitlist; TYPE_3__* wb_object; struct TYPE_9__* wb_next; int /*<<< orphan*/  wb_oldpri; TYPE_1__* wb_ext; } ;
typedef  TYPE_2__ wait_block ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct timeval {int tv_sec; int tv_usec; } ;
struct timespec {int tv_nsec; scalar_t__ tv_sec; } ;
struct thread {int /*<<< orphan*/  td_priority; } ;
struct TYPE_10__ {scalar_t__ dh_sigstate; scalar_t__ dh_type; int /*<<< orphan*/  dh_waitlisthead; } ;
typedef  TYPE_3__ nt_dispatch_header ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ DISP_TYPE_MUTANT ; 
 scalar_t__ FALSE ; 
 scalar_t__ INT32_MIN ; 
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MAX_WAIT_OBJECTS ; 
 int /*<<< orphan*/  RemoveEntryList (int /*<<< orphan*/ *) ; 
 int STATUS_INVALID_PARAMETER ; 
 int STATUS_SUCCESS ; 
 int STATUS_TIMEOUT ; 
 int STATUS_WAIT_0 ; 
 int THREAD_WAIT_OBJECTS ; 
 scalar_t__ TRUE ; 
 int WAITTYPE_ALL ; 
 int WAITTYPE_ANY ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int cv_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nanotime (struct timespec*) ; 
 int /*<<< orphan*/  ntoskrnl_dispatchlock ; 
 scalar_t__ ntoskrnl_is_signalled (TYPE_3__*,struct thread*) ; 
 int /*<<< orphan*/  ntoskrnl_satisfy_wait (TYPE_3__*,struct thread*) ; 
 int /*<<< orphan*/  ntoskrnl_time (scalar_t__*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  tvtohz (struct timeval*) ; 

__attribute__((used)) static uint32_t
KeWaitForMultipleObjects(uint32_t cnt, nt_dispatch_header *obj[], uint32_t wtype,
	uint32_t reason, uint32_t mode, uint8_t alertable, int64_t *duetime,
	wait_block *wb_array)
{
	struct thread		*td = curthread;
	wait_block		*whead, *w;
	wait_block		_wb_array[MAX_WAIT_OBJECTS];
	nt_dispatch_header	*cur;
	struct timeval		tv;
	int			i, wcnt = 0, error = 0;
	uint64_t		curtime;
	struct timespec		t1, t2;
	uint32_t		status = STATUS_SUCCESS;
	wb_ext			we;

	if (cnt > MAX_WAIT_OBJECTS)
		return (STATUS_INVALID_PARAMETER);
	if (cnt > THREAD_WAIT_OBJECTS && wb_array == NULL)
		return (STATUS_INVALID_PARAMETER);

	mtx_lock(&ntoskrnl_dispatchlock);

	cv_init(&we.we_cv, "KeWFM");
	we.we_td = td;

	if (wb_array == NULL)
		whead = _wb_array;
	else
		whead = wb_array;

	bzero((char *)whead, sizeof(wait_block) * cnt);

	/* First pass: see if we can satisfy any waits immediately. */

	wcnt = 0;
	w = whead;

	for (i = 0; i < cnt; i++) {
		InsertTailList((&obj[i]->dh_waitlisthead),
		    (&w->wb_waitlist));
		w->wb_ext = &we;
		w->wb_object = obj[i];
		w->wb_waittype = wtype;
		w->wb_waitkey = i;
		w->wb_awakened = FALSE;
		w->wb_oldpri = td->td_priority;
		w->wb_next = w + 1;
		w++;
		wcnt++;
		if (ntoskrnl_is_signalled(obj[i], td)) {
			/*
			 * There's a limit to how many times
			 * we can recursively acquire a mutant.
			 * If we hit the limit, something
			 * is very wrong.
			 */
			if (obj[i]->dh_sigstate == INT32_MIN &&
			    obj[i]->dh_type == DISP_TYPE_MUTANT) {
				mtx_unlock(&ntoskrnl_dispatchlock);
				panic("mutant limit exceeded");
			}

			/*
			 * If this is a WAITTYPE_ANY wait, then
			 * satisfy the waited object and exit
			 * right now.
			 */

			if (wtype == WAITTYPE_ANY) {
				ntoskrnl_satisfy_wait(obj[i], td);
				status = STATUS_WAIT_0 + i;
				goto wait_done;
			} else {
				w--;
				wcnt--;
				w->wb_object = NULL;
				RemoveEntryList(&w->wb_waitlist);
			}
		}
	}

	/*
	 * If this is a WAITTYPE_ALL wait and all objects are
	 * already signalled, satisfy the waits and exit now.
	 */

	if (wtype == WAITTYPE_ALL && wcnt == 0) {
		for (i = 0; i < cnt; i++)
			ntoskrnl_satisfy_wait(obj[i], td);
		status = STATUS_SUCCESS;
		goto wait_done;
	}

	/*
	 * Create a circular waitblock list. The waitcount
	 * must always be non-zero when we get here.
	 */

	(w - 1)->wb_next = whead;

	/* Wait on any objects that aren't yet signalled. */

	/* Calculate timeout, if any. */

	if (duetime != NULL) {
		if (*duetime < 0) {
			tv.tv_sec = - (*duetime) / 10000000;
			tv.tv_usec = (- (*duetime) / 10) -
			    (tv.tv_sec * 1000000);
		} else {
			ntoskrnl_time(&curtime);
			if (*duetime < curtime)
				tv.tv_sec = tv.tv_usec = 0;
			else {
				tv.tv_sec = ((*duetime) - curtime) / 10000000;
				tv.tv_usec = ((*duetime) - curtime) / 10 -
				    (tv.tv_sec * 1000000);
			}
		}
	}

	while (wcnt) {
		nanotime(&t1);

		if (duetime == NULL)
			cv_wait(&we.we_cv, &ntoskrnl_dispatchlock);
		else
			error = cv_timedwait(&we.we_cv,
			    &ntoskrnl_dispatchlock, tvtohz(&tv));

		/* Wait with timeout expired. */

		if (error) {
			status = STATUS_TIMEOUT;
			goto wait_done;
		}

		nanotime(&t2);

		/* See what's been signalled. */

		w = whead;
		do {
			cur = w->wb_object;
			if (ntoskrnl_is_signalled(cur, td) == TRUE ||
			    w->wb_awakened == TRUE) {
				/* Sanity check the signal state value. */
				if (cur->dh_sigstate == INT32_MIN &&
				    cur->dh_type == DISP_TYPE_MUTANT) {
					mtx_unlock(&ntoskrnl_dispatchlock);
					panic("mutant limit exceeded");
				}
				wcnt--;
				if (wtype == WAITTYPE_ANY) {
					status = w->wb_waitkey &
					    STATUS_WAIT_0;
					goto wait_done;
				}
			}
			w = w->wb_next;
		} while (w != whead);

		/*
		 * If all objects have been signalled, or if this
		 * is a WAITTYPE_ANY wait and we were woke up by
		 * someone, we can bail.
		 */

		if (wcnt == 0) {
			status = STATUS_SUCCESS;
			goto wait_done;
		}

		/*
		 * If this is WAITTYPE_ALL wait, and there's still
		 * objects that haven't been signalled, deduct the
		 * time that's elapsed so far from the timeout and
		 * wait again (or continue waiting indefinitely if
		 * there's no timeout).
		 */

		if (duetime != NULL) {
			tv.tv_sec -= (t2.tv_sec - t1.tv_sec);
			tv.tv_usec -= (t2.tv_nsec - t1.tv_nsec) / 1000;
		}
	}


wait_done:

	cv_destroy(&we.we_cv);

	for (i = 0; i < cnt; i++) {
		if (whead[i].wb_object != NULL)
			RemoveEntryList(&whead[i].wb_waitlist);

	}
	mtx_unlock(&ntoskrnl_dispatchlock);

	return (status);
}