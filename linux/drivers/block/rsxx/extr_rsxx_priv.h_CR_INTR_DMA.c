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

/* Variables and functions */
#define  CR_INTR_DMA0 135 
#define  CR_INTR_DMA1 134 
#define  CR_INTR_DMA2 133 
#define  CR_INTR_DMA3 132 
#define  CR_INTR_DMA4 131 
#define  CR_INTR_DMA5 130 
#define  CR_INTR_DMA6 129 
#define  CR_INTR_DMA7 128 

__attribute__((used)) static inline int CR_INTR_DMA(int N)
{
	static const unsigned int _CR_INTR_DMA[] = {
		CR_INTR_DMA0, CR_INTR_DMA1, CR_INTR_DMA2, CR_INTR_DMA3,
		CR_INTR_DMA4, CR_INTR_DMA5, CR_INTR_DMA6, CR_INTR_DMA7
	};
	return _CR_INTR_DMA[N];
}