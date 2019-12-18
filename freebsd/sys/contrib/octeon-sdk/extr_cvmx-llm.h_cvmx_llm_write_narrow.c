#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {scalar_t__ xxor; int /*<<< orphan*/  dat; scalar_t__ mbz; } ;
struct TYPE_6__ {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_llm_data_t ;
struct TYPE_7__ {int /*<<< orphan*/  u64; } ;
typedef  TYPE_3__ cvmx_llm_address_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_MT_LLM_DATA (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_MT_LLM_WRITE_ADDR_INTERNAL (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cvmx_llm_write_narrow(cvmx_llm_address_t address, uint64_t value, int set)
{
    cvmx_llm_data_t data;
    data.s.mbz = 0;

    data.s.dat = value;

    data.s.xxor = 0;

    if (set)
    {
        CVMX_MT_LLM_DATA(1, data.u64);
        CVMX_MT_LLM_WRITE_ADDR_INTERNAL(1, address.u64);
    }
    else
    {
        CVMX_MT_LLM_DATA(0, data.u64);
        CVMX_MT_LLM_WRITE_ADDR_INTERNAL(0, address.u64);
    }
}