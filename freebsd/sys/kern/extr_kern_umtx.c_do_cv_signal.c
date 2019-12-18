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
typedef  int /*<<< orphan*/  uint32_t ;
struct umtx_key {int dummy; } ;
struct ucond {int /*<<< orphan*/  c_has_waiters; int /*<<< orphan*/  c_flags; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  GET_SHARE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_CV ; 
 int fueword32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int suword32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int umtx_key_get (struct ucond*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct umtx_key*) ; 
 int /*<<< orphan*/  umtx_key_release (struct umtx_key*) ; 
 int /*<<< orphan*/  umtxq_busy (struct umtx_key*) ; 
 int umtxq_count (struct umtx_key*) ; 
 int /*<<< orphan*/  umtxq_lock (struct umtx_key*) ; 
 int umtxq_signal (struct umtx_key*,int) ; 
 int /*<<< orphan*/  umtxq_unbusy (struct umtx_key*) ; 
 int /*<<< orphan*/  umtxq_unlock (struct umtx_key*) ; 

__attribute__((used)) static int
do_cv_signal(struct thread *td, struct ucond *cv)
{
	struct umtx_key key;
	int error, cnt, nwake;
	uint32_t flags;

	error = fueword32(&cv->c_flags, &flags);
	if (error == -1)
		return (EFAULT);
	if ((error = umtx_key_get(cv, TYPE_CV, GET_SHARE(flags), &key)) != 0)
		return (error);	
	umtxq_lock(&key);
	umtxq_busy(&key);
	cnt = umtxq_count(&key);
	nwake = umtxq_signal(&key, 1);
	if (cnt <= nwake) {
		umtxq_unlock(&key);
		error = suword32(&cv->c_has_waiters, 0);
		if (error == -1)
			error = EFAULT;
		umtxq_lock(&key);
	}
	umtxq_unbusy(&key);
	umtxq_unlock(&key);
	umtx_key_release(&key);
	return (error);
}