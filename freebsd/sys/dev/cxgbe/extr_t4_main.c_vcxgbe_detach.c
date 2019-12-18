#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vi_info {int /*<<< orphan*/  viid; TYPE_1__* pi; } ;
struct adapter {int /*<<< orphan*/  pf; int /*<<< orphan*/  mbox; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {struct adapter* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxgbe_vi_detach (struct vi_info*) ; 
 struct vi_info* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doom_vi (struct adapter*,struct vi_info*) ; 
 int /*<<< orphan*/  end_synchronized_op (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_free_vi (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vcxgbe_detach(device_t dev)
{
	struct vi_info *vi;
	struct adapter *sc;

	vi = device_get_softc(dev);
	sc = vi->pi->adapter;

	doom_vi(sc, vi);

	cxgbe_vi_detach(vi);
	t4_free_vi(sc, sc->mbox, sc->pf, 0, vi->viid);

	end_synchronized_op(sc, 0);

	return (0);
}