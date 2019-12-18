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
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int hash_get_nents (struct scatterlist*,int,int*) ; 

__attribute__((used)) static bool hash_dma_valid_data(struct scatterlist *sg, int datasize)
{
	bool aligned;

	/* Need to include at least one nent, else error */
	if (hash_get_nents(sg, datasize, &aligned) < 1)
		return false;

	return aligned;
}