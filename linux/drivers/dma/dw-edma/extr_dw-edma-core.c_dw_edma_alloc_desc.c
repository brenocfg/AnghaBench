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
struct dw_edma_desc {struct dw_edma_chan* chan; } ;
struct dw_edma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  dw_edma_alloc_chunk (struct dw_edma_desc*) ; 
 int /*<<< orphan*/  kfree (struct dw_edma_desc*) ; 
 struct dw_edma_desc* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct dw_edma_desc *dw_edma_alloc_desc(struct dw_edma_chan *chan)
{
	struct dw_edma_desc *desc;

	desc = kzalloc(sizeof(*desc), GFP_NOWAIT);
	if (unlikely(!desc))
		return NULL;

	desc->chan = chan;
	if (!dw_edma_alloc_chunk(desc)) {
		kfree(desc);
		return NULL;
	}

	return desc;
}