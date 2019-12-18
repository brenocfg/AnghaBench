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
struct TYPE_2__ {int /*<<< orphan*/  error; } ;
struct dma_fence_array {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  PENDING_ERROR ; 
 int /*<<< orphan*/  cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dma_fence_array_clear_pending_error(struct dma_fence_array *array)
{
	/* Clear the error flag if not actually set. */
	cmpxchg(&array->base.error, PENDING_ERROR, 0);
}