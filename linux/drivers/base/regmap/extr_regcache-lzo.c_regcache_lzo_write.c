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
struct regmap {unsigned int reg_stride; struct regcache_lzo_ctx** cache; } ;
struct regcache_lzo_ctx {void* dst; size_t dst_len; void* src; size_t src_len; int /*<<< orphan*/  sync_bmp; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (void*) ; 
 int regcache_lzo_compress_cache_block (struct regmap*,struct regcache_lzo_ctx*) ; 
 int regcache_lzo_decompress_cache_block (struct regmap*,struct regcache_lzo_ctx*) ; 
 int regcache_lzo_get_blkindex (struct regmap*,unsigned int) ; 
 int regcache_lzo_get_blkpos (struct regmap*,unsigned int) ; 
 scalar_t__ regcache_set_val (struct regmap*,void*,int,unsigned int) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int regcache_lzo_write(struct regmap *map,
			      unsigned int reg, unsigned int value)
{
	struct regcache_lzo_ctx *lzo_block, **lzo_blocks;
	int ret, blkindex, blkpos;
	size_t tmp_dst_len;
	void *tmp_dst;

	/* index of the compressed lzo block */
	blkindex = regcache_lzo_get_blkindex(map, reg);
	/* register index within the decompressed block */
	blkpos = regcache_lzo_get_blkpos(map, reg);
	lzo_blocks = map->cache;
	lzo_block = lzo_blocks[blkindex];

	/* save the pointer and length of the compressed block */
	tmp_dst = lzo_block->dst;
	tmp_dst_len = lzo_block->dst_len;

	/* prepare the source to be the compressed block */
	lzo_block->src = lzo_block->dst;
	lzo_block->src_len = lzo_block->dst_len;

	/* decompress the block */
	ret = regcache_lzo_decompress_cache_block(map, lzo_block);
	if (ret < 0) {
		kfree(lzo_block->dst);
		goto out;
	}

	/* write the new value to the cache */
	if (regcache_set_val(map, lzo_block->dst, blkpos, value)) {
		kfree(lzo_block->dst);
		goto out;
	}

	/* prepare the source to be the decompressed block */
	lzo_block->src = lzo_block->dst;
	lzo_block->src_len = lzo_block->dst_len;

	/* compress the block */
	ret = regcache_lzo_compress_cache_block(map, lzo_block);
	if (ret < 0) {
		kfree(lzo_block->dst);
		kfree(lzo_block->src);
		goto out;
	}

	/* set the bit so we know we have to sync this register */
	set_bit(reg / map->reg_stride, lzo_block->sync_bmp);
	kfree(tmp_dst);
	kfree(lzo_block->src);
	return 0;
out:
	lzo_block->dst = tmp_dst;
	lzo_block->dst_len = tmp_dst_len;
	return ret;
}