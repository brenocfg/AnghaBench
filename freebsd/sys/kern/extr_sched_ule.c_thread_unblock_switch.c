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
struct thread {int /*<<< orphan*/  td_lock; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_store_rel_ptr (uintptr_t volatile*,uintptr_t) ; 

__attribute__((used)) static inline void
thread_unblock_switch(struct thread *td, struct mtx *mtx)
{
	atomic_store_rel_ptr((volatile uintptr_t *)&td->td_lock,
	    (uintptr_t)mtx);
}