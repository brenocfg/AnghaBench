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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ size; scalar_t__ len; int /*<<< orphan*/  virt; } ;
typedef  TYPE_1__ ocs_dma_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_memcpy (int /*<<< orphan*/ ,void*,scalar_t__) ; 

int32_t
ocs_dma_copy_in(ocs_dma_t *dma, void *buffer, uint32_t buffer_length)
{
	if (!dma)
		return -1;
	if (!buffer)
		return -1;
	if (buffer_length == 0)
		return 0;
	if (buffer_length > dma->size)
		buffer_length = dma->size;
	ocs_memcpy(dma->virt, buffer, buffer_length);
	dma->len = buffer_length;
	return buffer_length;
}