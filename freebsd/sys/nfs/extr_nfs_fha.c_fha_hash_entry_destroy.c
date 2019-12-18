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
struct fha_hash_entry {scalar_t__ num_rw; scalar_t__ num_exclusive; scalar_t__ num_threads; int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_NFS_FHA ; 
 int /*<<< orphan*/  free (struct fha_hash_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fha_hash_entry_destroy(struct fha_hash_entry *e)
{

	mtx_assert(e->mtx, MA_OWNED);
	KASSERT(e->num_rw == 0,
	    ("%d reqs on destroyed fhe %p", e->num_rw, e));
	KASSERT(e->num_exclusive == 0,
	    ("%d exclusive reqs on destroyed fhe %p", e->num_exclusive, e));
	KASSERT(e->num_threads == 0,
	    ("%d threads on destroyed fhe %p", e->num_threads, e));
	free(e, M_NFS_FHA);
}