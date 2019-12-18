#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fha_hash_entry {int /*<<< orphan*/  num_threads; int /*<<< orphan*/  mtx; } ;
struct TYPE_4__ {scalar_t__ st_p2; } ;
typedef  TYPE_1__ SVCTHREAD ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_alink ; 

__attribute__((used)) static void
fha_hash_entry_remove_thread(struct fha_hash_entry *fhe, SVCTHREAD *thread)
{

	mtx_assert(fhe->mtx, MA_OWNED);
	KASSERT(thread->st_p2 == 0,
	    ("%d reqs on removed thread %p", thread->st_p2, thread));
	LIST_REMOVE(thread, st_alink);
	fhe->num_threads--;
}