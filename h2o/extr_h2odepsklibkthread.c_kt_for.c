#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_4__ {int i; TYPE_2__* t; } ;
typedef  TYPE_1__ ktf_worker_t ;
struct TYPE_5__ {void (* func ) (void*,long,int) ;int n_threads; long n; TYPE_1__* w; void* data; } ;
typedef  TYPE_2__ kt_for_t ;

/* Variables and functions */
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  ktf_worker ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kt_for(int n_threads, void (*func)(void*,long,int), void *data, long n)
{
	int i;
	kt_for_t t;
	pthread_t *tid;
	t.func = func, t.data = data, t.n_threads = n_threads, t.n = n;
	t.w = (ktf_worker_t*)alloca(n_threads * sizeof(ktf_worker_t));
	tid = (pthread_t*)alloca(n_threads * sizeof(pthread_t));
	for (i = 0; i < n_threads; ++i)
		t.w[i].t = &t, t.w[i].i = i;
	for (i = 0; i < n_threads; ++i) pthread_create(&tid[i], 0, ktf_worker, &t.w[i]);
	for (i = 0; i < n_threads; ++i) pthread_join(tid[i], 0);
}