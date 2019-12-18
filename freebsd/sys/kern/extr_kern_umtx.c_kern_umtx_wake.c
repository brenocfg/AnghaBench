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
struct umtx_key {int dummy; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_SHARE ; 
 int /*<<< orphan*/  THREAD_SHARE ; 
 int /*<<< orphan*/  TYPE_SIMPLE_WAIT ; 
 int umtx_key_get (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct umtx_key*) ; 
 int /*<<< orphan*/  umtx_key_release (struct umtx_key*) ; 
 int /*<<< orphan*/  umtxq_lock (struct umtx_key*) ; 
 int /*<<< orphan*/  umtxq_signal (struct umtx_key*,int) ; 
 int /*<<< orphan*/  umtxq_unlock (struct umtx_key*) ; 

int
kern_umtx_wake(struct thread *td, void *uaddr, int n_wake, int is_private)
{
	struct umtx_key key;
	int ret;
	
	if ((ret = umtx_key_get(uaddr, TYPE_SIMPLE_WAIT,
	    is_private ? THREAD_SHARE : AUTO_SHARE, &key)) != 0)
		return (ret);
	umtxq_lock(&key);
	umtxq_signal(&key, n_wake);
	umtxq_unlock(&key);
	umtx_key_release(&key);
	return (0);
}