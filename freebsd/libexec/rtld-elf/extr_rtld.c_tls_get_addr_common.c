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
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
 scalar_t__ __predict_true (int) ; 
 scalar_t__ tls_dtv_generation ; 
 void* tls_get_addr_slow (scalar_t__**,int,size_t) ; 

void *
tls_get_addr_common(Elf_Addr **dtvp, int index, size_t offset)
{
	Elf_Addr *dtv;

	dtv = *dtvp;
	/* Check dtv generation in case new modules have arrived */
	if (__predict_true(dtv[0] == tls_dtv_generation &&
	    dtv[index + 1] != 0))
		return ((void *)(dtv[index + 1] + offset));
	return (tls_get_addr_slow(dtvp, index, offset));
}