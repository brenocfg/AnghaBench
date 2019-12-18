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
struct regmap_range_node {int dummy; } ;
struct TYPE_4__ {unsigned int val_bytes; scalar_t__ pad_bytes; scalar_t__ reg_bytes; int /*<<< orphan*/  (* format_reg ) (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ;} ;
struct regmap {TYPE_2__ format; int /*<<< orphan*/  work_buf; int /*<<< orphan*/  bus_context; TYPE_1__* bus; int /*<<< orphan*/  read_flag_mask; int /*<<< orphan*/  reg_shift; } ;
struct TYPE_3__ {int (* read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void*,unsigned int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct regmap_range_node* _regmap_range_lookup (struct regmap*,unsigned int) ; 
 int _regmap_select_page (struct regmap*,unsigned int*,struct regmap_range_node*,unsigned int) ; 
 int /*<<< orphan*/  regmap_set_work_buf_flag_mask (struct regmap*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void*,unsigned int) ; 
 int /*<<< orphan*/  trace_regmap_hw_read_done (struct regmap*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  trace_regmap_hw_read_start (struct regmap*,unsigned int,unsigned int) ; 

__attribute__((used)) static int _regmap_raw_read(struct regmap *map, unsigned int reg, void *val,
			    unsigned int val_len)
{
	struct regmap_range_node *range;
	int ret;

	WARN_ON(!map->bus);

	if (!map->bus || !map->bus->read)
		return -EINVAL;

	range = _regmap_range_lookup(map, reg);
	if (range) {
		ret = _regmap_select_page(map, &reg, range,
					  val_len / map->format.val_bytes);
		if (ret != 0)
			return ret;
	}

	map->format.format_reg(map->work_buf, reg, map->reg_shift);
	regmap_set_work_buf_flag_mask(map, map->format.reg_bytes,
				      map->read_flag_mask);
	trace_regmap_hw_read_start(map, reg, val_len / map->format.val_bytes);

	ret = map->bus->read(map->bus_context, map->work_buf,
			     map->format.reg_bytes + map->format.pad_bytes,
			     val, val_len);

	trace_regmap_hw_read_done(map, reg, val_len / map->format.val_bytes);

	return ret;
}