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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */

void * MemSet8(void* pDst, int c, uint32_t size)
{
    uint32_t i;

    for(i = 0; i < size; ++i)
        *(((uint8_t*)(pDst)) + i) = (uint8_t)(c);

    return pDst;
}