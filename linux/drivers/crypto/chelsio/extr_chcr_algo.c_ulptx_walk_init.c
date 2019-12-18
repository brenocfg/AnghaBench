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
struct ulptx_walk {scalar_t__ last_sg_len; int /*<<< orphan*/ * last_sg; int /*<<< orphan*/  pair; scalar_t__ pair_idx; scalar_t__ nents; struct ulptx_sgl* sgl; } ;
struct ulptx_sgl {int /*<<< orphan*/  sge; } ;

/* Variables and functions */

__attribute__((used)) static inline void ulptx_walk_init(struct ulptx_walk *walk,
				   struct ulptx_sgl *ulp)
{
	walk->sgl = ulp;
	walk->nents = 0;
	walk->pair_idx = 0;
	walk->pair = ulp->sge;
	walk->last_sg = NULL;
	walk->last_sg_len = 0;
}