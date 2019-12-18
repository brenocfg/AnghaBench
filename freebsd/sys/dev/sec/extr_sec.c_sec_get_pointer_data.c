#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct sec_desc {TYPE_1__* sd_ptr_dmem; } ;
struct TYPE_2__ {void* dma_vaddr; } ;

/* Variables and functions */

__attribute__((used)) static inline void *
sec_get_pointer_data(struct sec_desc *desc, u_int n)
{

	return (desc->sd_ptr_dmem[n].dma_vaddr);
}