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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  u64; } ;
typedef  TYPE_1__ cvmx_llm_address_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_MT_LLM_DATA (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_MT_LLM_WRITE64_ADDR_INTERNAL (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cvmx_llm_write_wide(cvmx_llm_address_t address, uint64_t value, int set)
{
    if (set)
    {
        CVMX_MT_LLM_DATA(1, value);
        CVMX_MT_LLM_WRITE64_ADDR_INTERNAL(1, address.u64);
    }
    else
    {
        CVMX_MT_LLM_DATA(0, value);
        CVMX_MT_LLM_WRITE64_ADDR_INTERNAL(0, address.u64);
    }
}