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
struct TYPE_2__ {int reg_bytes; int pad_bytes; unsigned int (* parse_val ) (void*) ;int /*<<< orphan*/  val_bytes; } ;
struct regmap {TYPE_1__ format; void* work_buf; } ;

/* Variables and functions */
 int EINVAL ; 
 int _regmap_raw_read (struct regmap*,unsigned int,void*,int /*<<< orphan*/ ) ; 
 unsigned int stub1 (void*) ; 

__attribute__((used)) static int _regmap_bus_read(void *context, unsigned int reg,
			    unsigned int *val)
{
	int ret;
	struct regmap *map = context;
	void *work_val = map->work_buf + map->format.reg_bytes +
		map->format.pad_bytes;

	if (!map->format.parse_val)
		return -EINVAL;

	ret = _regmap_raw_read(map, reg, work_val, map->format.val_bytes);
	if (ret == 0)
		*val = map->format.parse_val(work_val);

	return ret;
}