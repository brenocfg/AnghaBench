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
 int EOPNOTSUPP ; 
#define  MOD_LOAD 130 
#define  MOD_QUIESCE 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/ * ctxmith ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lp_tables_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * txmith ; 

__attribute__((used)) static int
lp_module_handler(module_t mod, int what, void *arg)
{

	switch (what) {
	case MOD_UNLOAD:
		mtx_lock(&lp_tables_lock);
		if (txmith != NULL) {
			free(txmith, M_DEVBUF);
			txmith = NULL;
		}
		if (ctxmith != NULL) {
			free(ctxmith, M_DEVBUF);
			ctxmith = NULL;
		}
		mtx_unlock(&lp_tables_lock);
		break;
	case MOD_LOAD:
	case MOD_QUIESCE:
		break;
	default:
		return (EOPNOTSUPP);
	}
	return (0);
}