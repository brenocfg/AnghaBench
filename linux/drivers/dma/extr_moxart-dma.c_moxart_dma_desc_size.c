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
struct moxart_desc {unsigned int sglen; TYPE_1__* sg; } ;
struct TYPE_2__ {scalar_t__ len; } ;

/* Variables and functions */

__attribute__((used)) static size_t moxart_dma_desc_size(struct moxart_desc *d,
				   unsigned int completed_sgs)
{
	unsigned int i;
	size_t size;

	for (size = i = completed_sgs; i < d->sglen; i++)
		size += d->sg[i].len;

	return size;
}