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
typedef  unsigned int u_int ;
struct openpic_softc {int dummy; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  OPENPIC_PCPU_IPI_DISPATCH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuid ; 
 struct openpic_softc* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  openpic_write (struct openpic_softc*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ root_pic ; 
 int /*<<< orphan*/  sched_pin () ; 
 int /*<<< orphan*/  sched_unpin () ; 

void
openpic_ipi(device_t dev, u_int cpu)
{
	struct openpic_softc *sc;

	KASSERT(dev == root_pic, ("Cannot send IPIs from non-root OpenPIC"));

	sc = device_get_softc(dev);
	sched_pin();
	openpic_write(sc, OPENPIC_PCPU_IPI_DISPATCH(PCPU_GET(cpuid), 0),
	    1u << cpu);
	sched_unpin();
}