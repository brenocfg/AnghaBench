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
struct ti_sci_handle {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct ti_sci_handle const* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct ti_sci_handle const*) ; 
 int /*<<< orphan*/  devm_ti_sci_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct ti_sci_handle const**) ; 
 struct ti_sci_handle** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct ti_sci_handle const**) ; 
 struct ti_sci_handle* ti_sci_get_handle (struct device*) ; 

const struct ti_sci_handle *devm_ti_sci_get_handle(struct device *dev)
{
	const struct ti_sci_handle **ptr;
	const struct ti_sci_handle *handle;

	ptr = devres_alloc(devm_ti_sci_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);
	handle = ti_sci_get_handle(dev);

	if (!IS_ERR(handle)) {
		*ptr = handle;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return handle;
}