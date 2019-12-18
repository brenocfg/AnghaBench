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
struct sched_param {int dummy; } ;
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  _pthread_attr_getguardsize (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  _pthread_attr_getinheritsched (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  _pthread_attr_getschedparam (int /*<<< orphan*/ *,struct sched_param*) ; 
 int /*<<< orphan*/  _pthread_attr_getschedpolicy (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  _pthread_attr_getscope (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  _pthread_attr_getstackaddr (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  _pthread_attr_getstacksize (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  _pthread_attr_setguardsize (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  _pthread_attr_setinheritsched (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _pthread_attr_setschedparam (int /*<<< orphan*/ *,struct sched_param*) ; 
 int /*<<< orphan*/  _pthread_attr_setschedpolicy (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _pthread_attr_setscope (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _pthread_attr_setstackaddr (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  _pthread_attr_setstacksize (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
attrcopy(pthread_attr_t *src, pthread_attr_t *dst)
{
	struct sched_param sched;
	void *a;
	size_t u;
	int v;

	_pthread_attr_getschedpolicy(src, &v);
	_pthread_attr_setschedpolicy(dst, v);

	_pthread_attr_getinheritsched(src, &v);
	_pthread_attr_setinheritsched(dst, v);

	_pthread_attr_getschedparam(src, &sched);
	_pthread_attr_setschedparam(dst, &sched);

	_pthread_attr_getscope(src, &v);
	_pthread_attr_setscope(dst, v);

	_pthread_attr_getstacksize(src, &u);
	_pthread_attr_setstacksize(dst, u);

	_pthread_attr_getstackaddr(src, &a);
	_pthread_attr_setstackaddr(src, a);

	_pthread_attr_getguardsize(src, &u);
	_pthread_attr_setguardsize(dst, u);
}