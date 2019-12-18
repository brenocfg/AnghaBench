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
struct TYPE_2__ {int /*<<< orphan*/  val_bytes; scalar_t__ pad_bytes; scalar_t__ reg_bytes; int /*<<< orphan*/  (* format_val ) (scalar_t__,unsigned int,int /*<<< orphan*/ ) ;} ;
struct regmap {TYPE_1__ format; scalar_t__ work_buf; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int _regmap_raw_write_impl (struct regmap*,unsigned int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _regmap_bus_raw_write(void *context, unsigned int reg,
				 unsigned int val)
{
	struct regmap *map = context;

	WARN_ON(!map->bus || !map->format.format_val);

	map->format.format_val(map->work_buf + map->format.reg_bytes
			       + map->format.pad_bytes, val, 0);
	return _regmap_raw_write_impl(map, reg,
				      map->work_buf +
				      map->format.reg_bytes +
				      map->format.pad_bytes,
				      map->format.val_bytes);
}