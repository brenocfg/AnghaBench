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
struct regmap_field {int dummy; } ;
struct regmap {int dummy; } ;
struct reg_field {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct regmap_field* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct regmap_field* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_field_init (struct regmap_field*,struct regmap*,struct reg_field) ; 

struct regmap_field *regmap_field_alloc(struct regmap *regmap,
		struct reg_field reg_field)
{
	struct regmap_field *rm_field = kzalloc(sizeof(*rm_field), GFP_KERNEL);

	if (!rm_field)
		return ERR_PTR(-ENOMEM);

	regmap_field_init(rm_field, regmap, reg_field);

	return rm_field;
}