#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {struct TYPE_8__* mdl_next; int /*<<< orphan*/  mdl_flags; } ;
typedef  TYPE_1__ mdl ;
struct TYPE_9__ {TYPE_1__* irp_mdl; } ;
typedef  TYPE_2__ irp ;

/* Variables and functions */
 TYPE_1__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDL_ZONE_ALLOCED ; 
 scalar_t__ MDL_ZONE_SIZE ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  MmInitializeMdl (TYPE_1__*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ MmSizeOfMdl (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  mdl_zone ; 
 int /*<<< orphan*/  panic (char*) ; 
 TYPE_1__* uma_zalloc (int /*<<< orphan*/ ,int) ; 

mdl *
IoAllocateMdl(void *vaddr, uint32_t len, uint8_t secondarybuf,
	uint8_t chargequota, irp *iopkt)
{
	mdl			*m;
	int			zone = 0;

	if (MmSizeOfMdl(vaddr, len) > MDL_ZONE_SIZE)
		m = ExAllocatePoolWithTag(NonPagedPool,
		    MmSizeOfMdl(vaddr, len), 0);
	else {
		m = uma_zalloc(mdl_zone, M_NOWAIT | M_ZERO);
		zone++;
	}

	if (m == NULL)
		return (NULL);

	MmInitializeMdl(m, vaddr, len);

	/*
	 * MmInitializMdl() clears the flags field, so we
	 * have to set this here. If the MDL came from the
	 * MDL UMA zone, tag it so we can release it to
	 * the right place later.
	 */
	if (zone)
		m->mdl_flags = MDL_ZONE_ALLOCED;

	if (iopkt != NULL) {
		if (secondarybuf == TRUE) {
			mdl			*last;
			last = iopkt->irp_mdl;
			while (last->mdl_next != NULL)
				last = last->mdl_next;
			last->mdl_next = m;
		} else {
			if (iopkt->irp_mdl != NULL)
				panic("leaking an MDL in IoAllocateMdl()");
			iopkt->irp_mdl = m;
		}
	}

	return (m);
}