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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  attribute_container_add_device (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transport_setup_classdev ; 

void transport_setup_device(struct device *dev)
{
	attribute_container_add_device(dev, transport_setup_classdev);
}