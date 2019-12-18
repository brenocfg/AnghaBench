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
struct pthread_atfork {void (* prepare ) () ;void (* parent ) () ;void (* child ) () ;} ;
struct pthread {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pthread_atfork*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THR_CRITICAL_ENTER (struct pthread*) ; 
 int /*<<< orphan*/  THR_CRITICAL_LEAVE (struct pthread*) ; 
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  _thr_atfork_list ; 
 int /*<<< orphan*/  _thr_atfork_lock ; 
 int /*<<< orphan*/  _thr_check_init () ; 
 int /*<<< orphan*/  _thr_rwl_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _thr_rwl_wrlock (int /*<<< orphan*/ *) ; 
 struct pthread_atfork* malloc (int) ; 
 int /*<<< orphan*/  qe ; 

int
_thr_atfork(void (*prepare)(void), void (*parent)(void),
    void (*child)(void))
{
	struct pthread *curthread;
	struct pthread_atfork *af;

	_thr_check_init();

	if ((af = malloc(sizeof(struct pthread_atfork))) == NULL)
		return (ENOMEM);

	curthread = _get_curthread();
	af->prepare = prepare;
	af->parent = parent;
	af->child = child;
	THR_CRITICAL_ENTER(curthread);
	_thr_rwl_wrlock(&_thr_atfork_lock);
	TAILQ_INSERT_TAIL(&_thr_atfork_list, af, qe);
	_thr_rwl_unlock(&_thr_atfork_lock);
	THR_CRITICAL_LEAVE(curthread);
	return (0);
}