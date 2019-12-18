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
struct linux_dma_priv {int /*<<< orphan*/  dma_mask; } ;
struct dma_pool {size_t pool_entry_size; int /*<<< orphan*/  pool_ptree; int /*<<< orphan*/  pool_lock; int /*<<< orphan*/  pool_zone; int /*<<< orphan*/  pool_dmat; struct device* pool_device; } ;
struct device {int /*<<< orphan*/  bsddev; struct linux_dma_priv* dma_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MTX_DEF ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_obj_ctor ; 
 int /*<<< orphan*/  dma_pool_obj_dtor ; 
 int /*<<< orphan*/  dma_pool_obj_import ; 
 int /*<<< orphan*/  dma_pool_obj_release ; 
 int /*<<< orphan*/  kfree (struct dma_pool*) ; 
 struct dma_pool* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pctrie_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zcache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dma_pool*,int /*<<< orphan*/ ) ; 

struct dma_pool *
linux_dma_pool_create(char *name, struct device *dev, size_t size,
    size_t align, size_t boundary)
{
	struct linux_dma_priv *priv;
	struct dma_pool *pool;

	priv = dev->dma_priv;

	pool = kzalloc(sizeof(*pool), GFP_KERNEL);
	pool->pool_device = dev;
	pool->pool_entry_size = size;

	if (bus_dma_tag_create(bus_get_dma_tag(dev->bsddev),
	    align, boundary,		/* alignment, boundary */
	    priv->dma_mask,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filtfunc, filtfuncarg */
	    size,			/* maxsize */
	    1,				/* nsegments */
	    size,			/* maxsegsz */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockfuncarg */
	    &pool->pool_dmat)) {
		kfree(pool);
		return (NULL);
	}

	pool->pool_zone = uma_zcache_create(name, -1, dma_pool_obj_ctor,
	    dma_pool_obj_dtor, NULL, NULL, dma_pool_obj_import,
	    dma_pool_obj_release, pool, 0);

	mtx_init(&pool->pool_lock, "lkpi-dma-pool", NULL, MTX_DEF);
	pctrie_init(&pool->pool_ptree);

	return (pool);
}