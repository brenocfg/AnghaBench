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
typedef  int /*<<< orphan*/  uint32_t ;
struct otus_softc {size_t write_idx; TYPE_1__* write_buf; } ;
struct TYPE_2__ {void* val; void* reg; } ;

/* Variables and functions */
 int AR_MAX_WRITE_IDX ; 
 int /*<<< orphan*/  OTUS_LOCK_ASSERT (struct otus_softc*) ; 
 void* htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otus_write_barrier (struct otus_softc*) ; 

void
otus_write(struct otus_softc *sc, uint32_t reg, uint32_t val)
{

	OTUS_LOCK_ASSERT(sc);

	sc->write_buf[sc->write_idx].reg = htole32(reg);
	sc->write_buf[sc->write_idx].val = htole32(val);

	if (++sc->write_idx > (AR_MAX_WRITE_IDX-1))
		(void)otus_write_barrier(sc);
}