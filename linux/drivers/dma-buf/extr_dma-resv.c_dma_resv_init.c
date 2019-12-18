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
struct dma_resv {int /*<<< orphan*/  fence_excl; int /*<<< orphan*/  fence; int /*<<< orphan*/  seq; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __seqcount_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reservation_seqcount_class ; 
 int /*<<< orphan*/  reservation_seqcount_string ; 
 int /*<<< orphan*/  reservation_ww_class ; 
 int /*<<< orphan*/  ww_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void dma_resv_init(struct dma_resv *obj)
{
	ww_mutex_init(&obj->lock, &reservation_ww_class);

	__seqcount_init(&obj->seq, reservation_seqcount_string,
			&reservation_seqcount_class);
	RCU_INIT_POINTER(obj->fence, NULL);
	RCU_INIT_POINTER(obj->fence_excl, NULL);
}