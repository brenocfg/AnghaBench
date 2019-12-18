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
typedef  int vm_offset_t ;
typedef  scalar_t__ u_long ;
typedef  int u_int8_t ;
typedef  int u_int32_t ;
typedef  int u_int16_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MP_GDT ; 
 scalar_t__ MPentry ; 
 int PAGE_SIZE ; 
 scalar_t__ bigJump ; 
 scalar_t__ bootCodeSeg ; 
 scalar_t__ bootDataSeg ; 
 scalar_t__ bootMP ; 
 int /*<<< orphan*/  bootMP_size ; 
 int boot_address ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  mp_gdtbase ; 
 int /*<<< orphan*/  pmap_invalidate_page (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_kenter (int,int) ; 

__attribute__((used)) static void
install_ap_tramp(void)
{
	int     x;
	int     size = *(int *) ((u_long) & bootMP_size);
	vm_offset_t va = boot_address;
	u_char *src = (u_char *) ((u_long) bootMP);
	u_char *dst = (u_char *) va;
	u_int   boot_base = (u_int) bootMP;
	u_int8_t *dst8;
	u_int16_t *dst16;
	u_int32_t *dst32;

	KASSERT (size <= PAGE_SIZE,
	    ("'size' do not fit into PAGE_SIZE, as expected."));
	pmap_kenter(va, boot_address);
	pmap_invalidate_page (kernel_pmap, va);
	for (x = 0; x < size; ++x)
		*dst++ = *src++;

	/*
	 * modify addresses in code we just moved to basemem. unfortunately we
	 * need fairly detailed info about mpboot.s for this to work.  changes
	 * to mpboot.s might require changes here.
	 */

	/* boot code is located in KERNEL space */
	dst = (u_char *) va;

	/* modify the lgdt arg */
	dst32 = (u_int32_t *) (dst + ((u_int) & mp_gdtbase - boot_base));
	*dst32 = boot_address + ((u_int) & MP_GDT - boot_base);

	/* modify the ljmp target for MPentry() */
	dst32 = (u_int32_t *) (dst + ((u_int) bigJump - boot_base) + 1);
	*dst32 = (u_int)MPentry;

	/* modify the target for boot code segment */
	dst16 = (u_int16_t *) (dst + ((u_int) bootCodeSeg - boot_base));
	dst8 = (u_int8_t *) (dst16 + 1);
	*dst16 = (u_int) boot_address & 0xffff;
	*dst8 = ((u_int) boot_address >> 16) & 0xff;

	/* modify the target for boot data segment */
	dst16 = (u_int16_t *) (dst + ((u_int) bootDataSeg - boot_base));
	dst8 = (u_int8_t *) (dst16 + 1);
	*dst16 = (u_int) boot_address & 0xffff;
	*dst8 = ((u_int) boot_address >> 16) & 0xff;
}