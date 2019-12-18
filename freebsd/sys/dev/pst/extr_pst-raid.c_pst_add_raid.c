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
struct pst_softc {struct i2o_lct_entry* lct; struct iop_softc* iop; } ;
struct iop_softc {int /*<<< orphan*/  dev; } ;
struct i2o_lct_entry {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_PSTRAID ; 
 int M_ZERO ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_probe_and_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_softc (int /*<<< orphan*/ ,struct pst_softc*) ; 
 struct pst_softc* malloc (int,int /*<<< orphan*/ ,int) ; 

int
pst_add_raid(struct iop_softc *sc, struct i2o_lct_entry *lct)
{
    struct pst_softc *psc;
    device_t child = device_add_child(sc->dev, "pst", -1);

    if (!child)
	return ENOMEM;
    if (!(psc = malloc(sizeof(struct pst_softc), 
		       M_PSTRAID, M_NOWAIT | M_ZERO))) {
	device_delete_child(sc->dev, child);
	return ENOMEM;
    }
    psc->iop = sc;
    psc->lct = lct;
    device_set_softc(child, psc);
    return device_probe_and_attach(child);
}