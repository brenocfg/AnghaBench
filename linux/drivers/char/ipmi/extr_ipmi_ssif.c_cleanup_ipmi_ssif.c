#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  address_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_ssif_clients () ; 
 int /*<<< orphan*/  i2c_del_driver (TYPE_1__*) ; 
 int initialized ; 
 int /*<<< orphan*/  ipmi_driver ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_driver_unregister (int /*<<< orphan*/ *) ; 
 scalar_t__ platform_registered ; 
 TYPE_1__ ssif_i2c_driver ; 
 scalar_t__ ssif_trydmi ; 

__attribute__((used)) static void cleanup_ipmi_ssif(void)
{
	if (!initialized)
		return;

	initialized = false;

	i2c_del_driver(&ssif_i2c_driver);

	kfree(ssif_i2c_driver.address_list);

	if (ssif_trydmi && platform_registered)
		platform_driver_unregister(&ipmi_driver);

	free_ssif_clients();
}