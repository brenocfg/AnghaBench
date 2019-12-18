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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct openpic_softc {scalar_t__ sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPENPIC_PCPU_TPR (int /*<<< orphan*/ ) ; 
 int OPENPIC_TPR_MASK ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuid ; 
 int openpic_read (struct openpic_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openpic_write (struct openpic_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ root_pic ; 
 int /*<<< orphan*/  sched_pin () ; 
 int /*<<< orphan*/  sched_unpin () ; 

__attribute__((used)) static __inline void
openpic_set_priority(struct openpic_softc *sc, int pri)
{
	u_int tpr;
	uint32_t x;

	sched_pin();
	tpr = OPENPIC_PCPU_TPR((sc->sc_dev == root_pic) ? PCPU_GET(cpuid) : 0);
	x = openpic_read(sc, tpr);
	x &= ~OPENPIC_TPR_MASK;
	x |= pri;
	openpic_write(sc, tpr, x);
	sched_unpin();
}