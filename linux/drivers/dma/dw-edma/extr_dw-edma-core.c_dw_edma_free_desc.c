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
struct dw_edma_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dw_edma_free_chunk (struct dw_edma_desc*) ; 
 int /*<<< orphan*/  kfree (struct dw_edma_desc*) ; 

__attribute__((used)) static void dw_edma_free_desc(struct dw_edma_desc *desc)
{
	dw_edma_free_chunk(desc);
	kfree(desc);
}