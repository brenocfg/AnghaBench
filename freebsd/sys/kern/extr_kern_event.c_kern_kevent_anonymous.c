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
struct thread {int dummy; } ;
struct kqueue {int kq_refcnt; } ;
struct kevent_copyops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kqueue_destroy (struct kqueue*) ; 
 int /*<<< orphan*/  kqueue_drain (struct kqueue*,struct thread*) ; 
 int /*<<< orphan*/  kqueue_init (struct kqueue*) ; 
 int kqueue_kevent (struct kqueue*,struct thread*,int,int,struct kevent_copyops*,int /*<<< orphan*/ *) ; 

int
kern_kevent_anonymous(struct thread *td, int nevents,
    struct kevent_copyops *k_ops)
{
	struct kqueue kq = {};
	int error;

	kqueue_init(&kq);
	kq.kq_refcnt = 1;
	error = kqueue_kevent(&kq, td, nevents, nevents, k_ops, NULL);
	kqueue_drain(&kq, td);
	kqueue_destroy(&kq);
	return (error);
}