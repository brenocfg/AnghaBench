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
struct emu_sc_info {int num_gprs; int /*<<< orphan*/  dev; struct emu_rm* rm; } ;
struct emu_rm {int num_gprs; int* allocmap; int last_free_gpr; int /*<<< orphan*/  gpr_lock; scalar_t__ num_used; struct emu_sc_info* card; } ;

/* Variables and functions */
 int EMU_MAX_GPR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct emu_rm* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
emu_rm_init(struct emu_sc_info *sc)
{
	int i;
	int maxcount;
	struct emu_rm *rm;

	rm = malloc(sizeof(struct emu_rm), M_DEVBUF, M_NOWAIT | M_ZERO);
	if (rm == NULL) {
		return (ENOMEM);
	}
	sc->rm = rm;
	rm->card = sc;
	maxcount = sc->num_gprs;
	rm->num_used = 0;
	mtx_init(&(rm->gpr_lock), device_get_nameunit(sc->dev), "gpr alloc", MTX_DEF);
	rm->num_gprs = (maxcount < EMU_MAX_GPR ? maxcount : EMU_MAX_GPR);
	for (i = 0; i < rm->num_gprs; i++)
		rm->allocmap[i] = 0;
	/* pre-allocate gpr[0] */
	rm->allocmap[0] = 1;
	rm->last_free_gpr = 1;

	return (0);
}