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
struct umtx_shm_reg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nitems (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umtx_shm_lock ; 
 int /*<<< orphan*/  umtx_shm_reg_zone ; 
 int /*<<< orphan*/ * umtx_shm_registry ; 

__attribute__((used)) static void
umtx_shm_init(void)
{
	int i;

	umtx_shm_reg_zone = uma_zcreate("umtx_shm", sizeof(struct umtx_shm_reg),
	    NULL, NULL, NULL, NULL, UMA_ALIGN_PTR, 0);
	mtx_init(&umtx_shm_lock, "umtxshm", NULL, MTX_DEF);
	for (i = 0; i < nitems(umtx_shm_registry); i++)
		TAILQ_INIT(&umtx_shm_registry[i]);
}