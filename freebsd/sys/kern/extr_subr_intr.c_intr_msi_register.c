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
typedef  int /*<<< orphan*/  uintmax_t ;
struct intr_pic {int dummy; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FLAG_MSI ; 
 int /*<<< orphan*/  debugf (char*,struct intr_pic*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ *) ; 
 struct intr_pic* pic_create (int /*<<< orphan*/ *,intptr_t,int /*<<< orphan*/ ) ; 

int
intr_msi_register(device_t dev, intptr_t xref)
{
	struct intr_pic *pic;

	if (dev == NULL)
		return (EINVAL);
	pic = pic_create(dev, xref, FLAG_MSI);
	if (pic == NULL)
		return (ENOMEM);

	debugf("PIC %p registered for %s <dev %p, xref %jx>\n", pic,
	    device_get_nameunit(dev), dev, (uintmax_t)xref);
	return (0);
}