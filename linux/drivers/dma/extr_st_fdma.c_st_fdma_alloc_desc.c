#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct st_fdma_desc {int n_nodes; TYPE_1__* node; struct st_fdma_chan* fchan; } ;
struct st_fdma_chan {int /*<<< orphan*/  node_pool; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdesc; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct st_fdma_desc*) ; 
 struct st_fdma_desc* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node ; 
 int /*<<< orphan*/  struct_size (struct st_fdma_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct st_fdma_desc *st_fdma_alloc_desc(struct st_fdma_chan *fchan,
					       int sg_len)
{
	struct st_fdma_desc *fdesc;
	int i;

	fdesc = kzalloc(struct_size(fdesc, node, sg_len), GFP_NOWAIT);
	if (!fdesc)
		return NULL;

	fdesc->fchan = fchan;
	fdesc->n_nodes = sg_len;
	for (i = 0; i < sg_len; i++) {
		fdesc->node[i].desc = dma_pool_alloc(fchan->node_pool,
				GFP_NOWAIT, &fdesc->node[i].pdesc);
		if (!fdesc->node[i].desc)
			goto err;
	}
	return fdesc;

err:
	while (--i >= 0)
		dma_pool_free(fchan->node_pool, fdesc->node[i].desc,
			      fdesc->node[i].pdesc);
	kfree(fdesc);
	return NULL;
}