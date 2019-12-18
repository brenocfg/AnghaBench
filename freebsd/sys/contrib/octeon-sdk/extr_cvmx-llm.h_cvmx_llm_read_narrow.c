#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  u64; } ;
typedef  TYPE_1__ cvmx_llm_data_t ;
struct TYPE_6__ {int /*<<< orphan*/  u64; } ;
typedef  TYPE_2__ cvmx_llm_address_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_MF_LLM_DATA (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_MT_LLM_READ_ADDR (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline cvmx_llm_data_t cvmx_llm_read_narrow(cvmx_llm_address_t address, int set)
{
    cvmx_llm_data_t value;
    if (set)
    {
        CVMX_MT_LLM_READ_ADDR(1, address.u64);
        CVMX_MF_LLM_DATA(1, value.u64);
    }
    else
    {
        CVMX_MT_LLM_READ_ADDR(0, address.u64);
        CVMX_MF_LLM_DATA(0, value.u64);
    }
    return value;
}