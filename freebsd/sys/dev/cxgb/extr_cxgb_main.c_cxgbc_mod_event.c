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
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EBUSY ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t3_list ; 
 int /*<<< orphan*/  t3_list_lock ; 
 int /*<<< orphan*/  t3_uld_list ; 
 int /*<<< orphan*/  t3_uld_list_lock ; 

__attribute__((used)) static int
cxgbc_mod_event(module_t mod, int cmd, void *arg)
{
	int rc = 0;

	switch (cmd) {
	case MOD_LOAD:
		mtx_init(&t3_list_lock, "T3 adapters", 0, MTX_DEF);
		SLIST_INIT(&t3_list);
#ifdef TCP_OFFLOAD
		mtx_init(&t3_uld_list_lock, "T3 ULDs", 0, MTX_DEF);
		SLIST_INIT(&t3_uld_list);
#endif
		break;

	case MOD_UNLOAD:
#ifdef TCP_OFFLOAD
		mtx_lock(&t3_uld_list_lock);
		if (!SLIST_EMPTY(&t3_uld_list)) {
			rc = EBUSY;
			mtx_unlock(&t3_uld_list_lock);
			break;
		}
		mtx_unlock(&t3_uld_list_lock);
		mtx_destroy(&t3_uld_list_lock);
#endif
		mtx_lock(&t3_list_lock);
		if (!SLIST_EMPTY(&t3_list)) {
			rc = EBUSY;
			mtx_unlock(&t3_list_lock);
			break;
		}
		mtx_unlock(&t3_list_lock);
		mtx_destroy(&t3_list_lock);
		break;
	}

	return (rc);
}