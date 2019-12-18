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

/* Variables and functions */
 int IDR_SIZE ; 
 int /*<<< orphan*/  M_IDR ; 
 int /*<<< orphan*/  free (struct idr_layer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
idr_remove_layer(struct idr_layer *il, int layer)
{
	int i;

	if (il == NULL)
		return;
	if (layer == 0) {
		free(il, M_IDR);
		return;
	}
	for (i = 0; i < IDR_SIZE; i++)
		if (il->ary[i])
			idr_remove_layer(il->ary[i], layer - 1);
}