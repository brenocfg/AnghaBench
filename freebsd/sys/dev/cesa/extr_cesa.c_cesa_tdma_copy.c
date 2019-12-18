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
struct cesa_tdma_desc {TYPE_1__* ctd_cthd; } ;
struct cesa_softc {int dummy; } ;
typedef  scalar_t__ bus_size_t ;
typedef  void* bus_addr_t ;
struct TYPE_2__ {scalar_t__ cthd_flags; scalar_t__ cthd_byte_count; void* cthd_src; void* cthd_dst; } ;

/* Variables and functions */
 scalar_t__ CESA_CTHD_OWNED ; 
 struct cesa_tdma_desc* cesa_alloc_tdesc (struct cesa_softc*) ; 

__attribute__((used)) static struct cesa_tdma_desc *
cesa_tdma_copy(struct cesa_softc *sc, bus_addr_t dst, bus_addr_t src,
    bus_size_t size)
{
	struct cesa_tdma_desc *ctd;

	ctd = cesa_alloc_tdesc(sc);
	if (!ctd)
		return (NULL);

	ctd->ctd_cthd->cthd_dst = dst;
	ctd->ctd_cthd->cthd_src = src;
	ctd->ctd_cthd->cthd_byte_count = size;

	/* Handle special control packet */
	if (size != 0)
		ctd->ctd_cthd->cthd_flags = CESA_CTHD_OWNED;
	else
		ctd->ctd_cthd->cthd_flags = 0;

	return (ctd);
}