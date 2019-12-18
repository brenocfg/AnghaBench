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
struct idr_layer {struct idr_layer** ary; } ;
struct idr {struct idr_layer* free; } ;

/* Variables and functions */

__attribute__((used)) static struct idr_layer *
idr_free_list_get(struct idr *idp)
{
	struct idr_layer *il;

	if ((il = idp->free) != NULL) {
		idp->free = il->ary[0];
		il->ary[0] = NULL;
	}
	return (il);
}