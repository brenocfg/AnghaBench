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
struct idr {scalar_t__ layers; int /*<<< orphan*/  top; } ;

/* Variables and functions */
 int idr_for_each_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int (*) (int,void*,void*),void*) ; 

int
idr_for_each(struct idr *idp, int (*f)(int id, void *p, void *data), void *data)
{
	return (idr_for_each_layer(idp->top, 0, idp->layers - 1, f, data));
}