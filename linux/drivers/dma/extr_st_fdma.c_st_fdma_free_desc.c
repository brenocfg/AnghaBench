#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct virt_dma_desc {int dummy; } ;
struct st_fdma_desc {int n_nodes; TYPE_2__* node; TYPE_1__* fchan; } ;
struct TYPE_4__ {int /*<<< orphan*/  pdesc; int /*<<< orphan*/  desc; } ;
struct TYPE_3__ {int /*<<< orphan*/  node_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct st_fdma_desc*) ; 
 struct st_fdma_desc* to_st_fdma_desc (struct virt_dma_desc*) ; 

__attribute__((used)) static void st_fdma_free_desc(struct virt_dma_desc *vdesc)
{
	struct st_fdma_desc *fdesc;
	int i;

	fdesc = to_st_fdma_desc(vdesc);
	for (i = 0; i < fdesc->n_nodes; i++)
		dma_pool_free(fdesc->fchan->node_pool, fdesc->node[i].desc,
			      fdesc->node[i].pdesc);
	kfree(fdesc);
}