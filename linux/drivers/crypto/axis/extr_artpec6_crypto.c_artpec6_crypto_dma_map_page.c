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
struct page {int dummy; } ;
struct device {int dummy; } ;
struct artpec6_crypto_req_common {struct artpec6_crypto_dma_descriptors* dma; } ;
struct artpec6_crypto_dma_map {size_t size; int dir; int /*<<< orphan*/  dma_addr; } ;
struct artpec6_crypto_dma_descriptors {scalar_t__ map_count; struct artpec6_crypto_dma_map* maps; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (struct artpec6_crypto_dma_map*) ; 
 int ENOMEM ; 
 struct device* artpec6_crypto_dev ; 
 int /*<<< orphan*/  dma_map_page (struct device*,struct page*,size_t,size_t,int) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int artpec6_crypto_dma_map_page(struct artpec6_crypto_req_common *common,
				      struct page *page, size_t offset,
				      size_t size,
				      enum dma_data_direction dir,
				      dma_addr_t *dma_addr_out)
{
	struct artpec6_crypto_dma_descriptors *dma = common->dma;
	struct device *dev = artpec6_crypto_dev;
	struct artpec6_crypto_dma_map *map;
	dma_addr_t dma_addr;

	*dma_addr_out = 0;

	if (dma->map_count >= ARRAY_SIZE(dma->maps))
		return -ENOMEM;

	dma_addr = dma_map_page(dev, page, offset, size, dir);
	if (dma_mapping_error(dev, dma_addr))
		return -ENOMEM;

	map = &dma->maps[dma->map_count++];
	map->size = size;
	map->dma_addr = dma_addr;
	map->dir = dir;

	*dma_addr_out = dma_addr;

	return 0;
}