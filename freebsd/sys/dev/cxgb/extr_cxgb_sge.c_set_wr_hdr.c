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
struct work_request_hdr {int wrh_hilo; } ;

/* Variables and functions */

__attribute__((used)) static void
set_wr_hdr(struct work_request_hdr *wrp, uint32_t wr_hi, uint32_t wr_lo)
{
	uint64_t wr_hilo;
#if _BYTE_ORDER == _LITTLE_ENDIAN
	wr_hilo = wr_hi;
	wr_hilo |= (((uint64_t)wr_lo)<<32);
#else
	wr_hilo = wr_lo;
	wr_hilo |= (((uint64_t)wr_hi)<<32);
#endif	
	wrp->wrh_hilo = wr_hilo;
}