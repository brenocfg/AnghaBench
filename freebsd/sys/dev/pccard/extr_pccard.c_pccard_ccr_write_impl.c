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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct pccard_ivar {struct pccard_function* pf; } ;
struct pccard_function {scalar_t__ pf_ccr_offset; int /*<<< orphan*/  pf_ccrh; int /*<<< orphan*/  pf_ccrt; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVPRINTF (int /*<<< orphan*/ ) ; 
 struct pccard_ivar* PCCARD_IVAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pccard_ccr_write_impl(device_t brdev, device_t child, uint32_t offset,
    uint8_t val)
{
	struct pccard_ivar *devi = PCCARD_IVAR(child);
	struct pccard_function *pf = devi->pf;

	/*
	 * Can't use pccard_ccr_write since client drivers may access
	 * registers not contained in the 'mask' if they are non-standard.
	 */
	DEVPRINTF((child, "ccr_write of %#x to %#x (%#x)\n", val, offset,
	  devi->pf->pf_ccr_offset));
	bus_space_write_1(pf->pf_ccrt, pf->pf_ccrh, pf->pf_ccr_offset + offset,
	    val);
	return 0;
}