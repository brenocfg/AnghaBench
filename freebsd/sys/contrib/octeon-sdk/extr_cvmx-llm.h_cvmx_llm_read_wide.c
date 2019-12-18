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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  cvmx_llm_address_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_MF_LLM_DATA (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_MT_LLM_READ64_ADDR (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint64_t cvmx_llm_read_wide(cvmx_llm_address_t address, int set)
{
    uint64_t value;
    if (set)
    {
        CVMX_MT_LLM_READ64_ADDR(1, address);
        CVMX_MF_LLM_DATA(1, value);
    }
    else
    {
        CVMX_MT_LLM_READ64_ADDR(0, address);
        CVMX_MF_LLM_DATA(0, value);
    }
    return value;
}