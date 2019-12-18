#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {scalar_t__ base; } ;
typedef  TYPE_1__ dcr_host_t ;

/* Variables and functions */
 scalar_t__ SDRAM_DCR_ADDR_OFFSET ; 
 scalar_t__ SDRAM_DCR_DATA_OFFSET ; 
 int /*<<< orphan*/  __mfdcri (scalar_t__,scalar_t__,unsigned int) ; 

__attribute__((used)) static inline u32
mfsdram(const dcr_host_t *dcr_host, unsigned int idcr_n)
{
	return __mfdcri(dcr_host->base + SDRAM_DCR_ADDR_OFFSET,
			dcr_host->base + SDRAM_DCR_DATA_OFFSET,
			idcr_n);
}