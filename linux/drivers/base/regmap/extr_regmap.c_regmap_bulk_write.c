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
typedef  unsigned int u8 ;
typedef  unsigned int u64 ;
typedef  unsigned int u32 ;
typedef  unsigned int u16 ;
struct TYPE_2__ {size_t val_bytes; int /*<<< orphan*/  (* parse_inplace ) (void*) ;} ;
struct regmap {TYPE_1__ format; int /*<<< orphan*/  alloc_flags; int /*<<< orphan*/  lock_arg; int /*<<< orphan*/  (* unlock ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* lock ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  bus; int /*<<< orphan*/  reg_stride; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned int,int /*<<< orphan*/ ) ; 
 int _regmap_write (struct regmap*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmemdup (void const*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ regmap_get_offset (struct regmap*,int) ; 
 int regmap_raw_write (struct regmap*,unsigned int,void*,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (void*) ; 

int regmap_bulk_write(struct regmap *map, unsigned int reg, const void *val,
		     size_t val_count)
{
	int ret = 0, i;
	size_t val_bytes = map->format.val_bytes;

	if (!IS_ALIGNED(reg, map->reg_stride))
		return -EINVAL;

	/*
	 * Some devices don't support bulk write, for them we have a series of
	 * single write operations.
	 */
	if (!map->bus || !map->format.parse_inplace) {
		map->lock(map->lock_arg);
		for (i = 0; i < val_count; i++) {
			unsigned int ival;

			switch (val_bytes) {
			case 1:
				ival = *(u8 *)(val + (i * val_bytes));
				break;
			case 2:
				ival = *(u16 *)(val + (i * val_bytes));
				break;
			case 4:
				ival = *(u32 *)(val + (i * val_bytes));
				break;
#ifdef CONFIG_64BIT
			case 8:
				ival = *(u64 *)(val + (i * val_bytes));
				break;
#endif
			default:
				ret = -EINVAL;
				goto out;
			}

			ret = _regmap_write(map,
					    reg + regmap_get_offset(map, i),
					    ival);
			if (ret != 0)
				goto out;
		}
out:
		map->unlock(map->lock_arg);
	} else {
		void *wval;

		wval = kmemdup(val, val_count * val_bytes, map->alloc_flags);
		if (!wval)
			return -ENOMEM;

		for (i = 0; i < val_count * val_bytes; i += val_bytes)
			map->format.parse_inplace(wval + i);

		ret = regmap_raw_write(map, reg, wval, val_bytes * val_count);

		kfree(wval);
	}
	return ret;
}