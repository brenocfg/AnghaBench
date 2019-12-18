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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {size_t val_bytes; } ;
struct regmap {size_t max_raw_write; int /*<<< orphan*/  lock_arg; int /*<<< orphan*/  (* unlock ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* lock ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  reg_stride; TYPE_2__ format; TYPE_1__* bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  write; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned int,int /*<<< orphan*/ ) ; 
 int _regmap_raw_write (struct regmap*,unsigned int,void const*,size_t) ; 
 int /*<<< orphan*/  regmap_volatile (struct regmap*,unsigned int) ; 
 int /*<<< orphan*/  regmap_writeable_noinc (struct regmap*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

int regmap_noinc_write(struct regmap *map, unsigned int reg,
		      const void *val, size_t val_len)
{
	size_t write_len;
	int ret;

	if (!map->bus)
		return -EINVAL;
	if (!map->bus->write)
		return -ENOTSUPP;
	if (val_len % map->format.val_bytes)
		return -EINVAL;
	if (!IS_ALIGNED(reg, map->reg_stride))
		return -EINVAL;
	if (val_len == 0)
		return -EINVAL;

	map->lock(map->lock_arg);

	if (!regmap_volatile(map, reg) || !regmap_writeable_noinc(map, reg)) {
		ret = -EINVAL;
		goto out_unlock;
	}

	while (val_len) {
		if (map->max_raw_write && map->max_raw_write < val_len)
			write_len = map->max_raw_write;
		else
			write_len = val_len;
		ret = _regmap_raw_write(map, reg, val, write_len);
		if (ret)
			goto out_unlock;
		val = ((u8 *)val) + write_len;
		val_len -= write_len;
	}

out_unlock:
	map->unlock(map->lock_arg);
	return ret;
}