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
struct regmap {size_t num_reg_defaults_raw; char* reg_defaults_raw; int cache_size_raw; struct regcache_lzo_ctx** cache; } ;
struct regcache_lzo_ctx {unsigned long* sync_bmp; size_t sync_bmp_nbits; char const* src; int src_len; int decompressed_size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bitmap_free (unsigned long*) ; 
 unsigned long* bitmap_zalloc (size_t,int /*<<< orphan*/ ) ; 
 struct regcache_lzo_ctx** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 struct regcache_lzo_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int regcache_lzo_block_count (struct regmap*) ; 
 int regcache_lzo_compress_cache_block (struct regmap*,struct regcache_lzo_ctx*) ; 
 int /*<<< orphan*/  regcache_lzo_exit (struct regmap*) ; 
 int regcache_lzo_get_blksize (struct regmap*) ; 
 int regcache_lzo_prepare (struct regcache_lzo_ctx*) ; 

__attribute__((used)) static int regcache_lzo_init(struct regmap *map)
{
	struct regcache_lzo_ctx **lzo_blocks;
	size_t bmp_size;
	int ret, i, blksize, blkcount;
	const char *p, *end;
	unsigned long *sync_bmp;

	ret = 0;

	blkcount = regcache_lzo_block_count(map);
	map->cache = kcalloc(blkcount, sizeof(*lzo_blocks),
			     GFP_KERNEL);
	if (!map->cache)
		return -ENOMEM;
	lzo_blocks = map->cache;

	/*
	 * allocate a bitmap to be used when syncing the cache with
	 * the hardware.  Each time a register is modified, the corresponding
	 * bit is set in the bitmap, so we know that we have to sync
	 * that register.
	 */
	bmp_size = map->num_reg_defaults_raw;
	sync_bmp = bitmap_zalloc(bmp_size, GFP_KERNEL);
	if (!sync_bmp) {
		ret = -ENOMEM;
		goto err;
	}

	/* allocate the lzo blocks and initialize them */
	for (i = 0; i < blkcount; i++) {
		lzo_blocks[i] = kzalloc(sizeof **lzo_blocks,
					GFP_KERNEL);
		if (!lzo_blocks[i]) {
			bitmap_free(sync_bmp);
			ret = -ENOMEM;
			goto err;
		}
		lzo_blocks[i]->sync_bmp = sync_bmp;
		lzo_blocks[i]->sync_bmp_nbits = bmp_size;
		/* alloc the working space for the compressed block */
		ret = regcache_lzo_prepare(lzo_blocks[i]);
		if (ret < 0)
			goto err;
	}

	blksize = regcache_lzo_get_blksize(map);
	p = map->reg_defaults_raw;
	end = map->reg_defaults_raw + map->cache_size_raw;
	/* compress the register map and fill the lzo blocks */
	for (i = 0; i < blkcount; i++, p += blksize) {
		lzo_blocks[i]->src = p;
		if (p + blksize > end)
			lzo_blocks[i]->src_len = end - p;
		else
			lzo_blocks[i]->src_len = blksize;
		ret = regcache_lzo_compress_cache_block(map,
						       lzo_blocks[i]);
		if (ret < 0)
			goto err;
		lzo_blocks[i]->decompressed_size =
			lzo_blocks[i]->src_len;
	}

	return 0;
err:
	regcache_lzo_exit(map);
	return ret;
}