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
struct tid_info {int ntids; int /*<<< orphan*/  hftid_cv; int /*<<< orphan*/  hftid_lock; int /*<<< orphan*/ * hftid_hash_4t; int /*<<< orphan*/  hftid_4t_mask; int /*<<< orphan*/ * hftid_hash_tid; int /*<<< orphan*/  hftid_tid_mask; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_CXGBE ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hashdestroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* hashinit_flags (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
alloc_hftid_hash(struct tid_info *t, int flags)
{
	int n;

	MPASS(t->ntids > 0);
	MPASS(t->hftid_hash_4t == NULL);
	MPASS(t->hftid_hash_tid == NULL);

	n = max(t->ntids / 1024, 16);
	t->hftid_hash_4t = hashinit_flags(n, M_CXGBE, &t->hftid_4t_mask, flags);
	if (t->hftid_hash_4t == NULL)
		return (ENOMEM);
	t->hftid_hash_tid = hashinit_flags(n, M_CXGBE, &t->hftid_tid_mask,
	    flags);
	if (t->hftid_hash_tid == NULL) {
		hashdestroy(t->hftid_hash_4t, M_CXGBE, t->hftid_4t_mask);
		t->hftid_hash_4t = NULL;
		return (ENOMEM);
	}

	mtx_init(&t->hftid_lock, "T4 hashfilters", 0, MTX_DEF);
	cv_init(&t->hftid_cv, "t4hfcv");

	return (0);
}