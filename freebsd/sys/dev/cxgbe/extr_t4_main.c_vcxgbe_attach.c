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
struct vi_info {int /*<<< orphan*/  viid; struct port_info* pi; } ;
struct port_info {struct adapter* adapter; } ;
struct adapter {int /*<<< orphan*/  pf; int /*<<< orphan*/  mbox; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int INTR_OK ; 
 int SLEEP_OK ; 
 int alloc_extra_vi (struct adapter*,struct port_info*,struct vi_info*) ; 
 int begin_synchronized_op (struct adapter*,struct vi_info*,int,char*) ; 
 int cxgbe_vi_attach (int /*<<< orphan*/ ,struct vi_info*) ; 
 struct vi_info* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_synchronized_op (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_free_vi (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vcxgbe_attach(device_t dev)
{
	struct vi_info *vi;
	struct port_info *pi;
	struct adapter *sc;
	int rc;

	vi = device_get_softc(dev);
	pi = vi->pi;
	sc = pi->adapter;

	rc = begin_synchronized_op(sc, vi, SLEEP_OK | INTR_OK, "t4via");
	if (rc)
		return (rc);
	rc = alloc_extra_vi(sc, pi, vi);
	end_synchronized_op(sc, 0);
	if (rc)
		return (rc);

	rc = cxgbe_vi_attach(dev, vi);
	if (rc) {
		t4_free_vi(sc, sc->mbox, sc->pf, 0, vi->viid);
		return (rc);
	}
	return (0);
}