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
struct __qm_mcr_querycongestion {int* __state; } ;

/* Variables and functions */
 int __CGR_SHIFT (int /*<<< orphan*/ ) ; 
 size_t __CGR_WORD (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ int QM_MCR_QUERYCONGESTION(struct __qm_mcr_querycongestion *p,
                    uint8_t cgr)
{
    return (int)(p->__state[__CGR_WORD(cgr)] & (0x80000000 >> __CGR_SHIFT(cgr)));
}