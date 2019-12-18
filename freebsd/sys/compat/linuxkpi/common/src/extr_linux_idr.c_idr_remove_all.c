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
struct idr {int /*<<< orphan*/  lock; scalar_t__ layers; int /*<<< orphan*/ * top; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove_layer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
idr_remove_all(struct idr *idr)
{

	mtx_lock(&idr->lock);
	idr_remove_layer(idr->top, idr->layers - 1);
	idr->top = NULL;
	idr->layers = 0;
	mtx_unlock(&idr->lock);
}