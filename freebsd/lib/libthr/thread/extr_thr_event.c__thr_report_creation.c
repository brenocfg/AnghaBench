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
struct TYPE_2__ {uintptr_t th_p; scalar_t__ data; int /*<<< orphan*/  event; } ;
struct pthread {TYPE_1__ event_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  TD_CREATE ; 
 int /*<<< orphan*/  THR_UMUTEX_LOCK (struct pthread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THR_UMUTEX_UNLOCK (struct pthread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _thr_event_lock ; 
 int /*<<< orphan*/  _thread_bp_create () ; 
 struct pthread* _thread_last_event ; 

void
_thr_report_creation(struct pthread *curthread, struct pthread *newthread)
{
	curthread->event_buf.event = TD_CREATE;
	curthread->event_buf.th_p = (uintptr_t)newthread;
	curthread->event_buf.data = 0;
	THR_UMUTEX_LOCK(curthread, &_thr_event_lock);
	_thread_last_event = curthread;
	_thread_bp_create();
	_thread_last_event = NULL;
	THR_UMUTEX_UNLOCK(curthread, &_thr_event_lock);
}