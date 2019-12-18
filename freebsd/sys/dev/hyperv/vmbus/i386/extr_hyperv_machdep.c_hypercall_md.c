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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */

uint64_t
hypercall_md(volatile void *hc_addr, uint64_t in_val,
    uint64_t in_paddr, uint64_t out_paddr)
{
	uint32_t in_val_hi = in_val >> 32;
	uint32_t in_val_lo = in_val & 0xFFFFFFFF;
	uint32_t status_hi, status_lo;
	uint32_t in_paddr_hi = in_paddr >> 32;
	uint32_t in_paddr_lo = in_paddr & 0xFFFFFFFF;
	uint32_t out_paddr_hi = out_paddr >> 32;
	uint32_t out_paddr_lo = out_paddr & 0xFFFFFFFF;

	__asm__ __volatile__ ("call *%8" : "=d"(status_hi), "=a"(status_lo) :
	    "d" (in_val_hi), "a" (in_val_lo),
	    "b" (in_paddr_hi), "c" (in_paddr_lo),
	    "D"(out_paddr_hi), "S"(out_paddr_lo),
	    "m" (hc_addr));
	return (status_lo | ((uint64_t)status_hi << 32));
}