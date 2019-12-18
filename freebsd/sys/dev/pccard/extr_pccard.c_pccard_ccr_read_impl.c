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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct pccard_ivar {TYPE_1__* pf; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  pf_ccr_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVPRINTF (int /*<<< orphan*/ ) ; 
 struct pccard_ivar* PCCARD_IVAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pccard_ccr_read (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pccard_ccr_read_impl(device_t brdev, device_t child, uint32_t offset,
    uint8_t *val)
{
	struct pccard_ivar *devi = PCCARD_IVAR(child);

	*val = pccard_ccr_read(devi->pf, offset);
	DEVPRINTF((child, "ccr_read of %#x (%#x) is %#x\n", offset,
	  devi->pf->pf_ccr_offset, *val));
	return 0;
}