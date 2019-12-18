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
struct artpec6_crypto_walk {scalar_t__ offset; struct scatterlist* sg; } ;

/* Variables and functions */

__attribute__((used)) static void artpec6_crypto_walk_init(struct artpec6_crypto_walk *awalk,
				     struct scatterlist *sg)
{
	awalk->sg = sg;
	awalk->offset = 0;
}