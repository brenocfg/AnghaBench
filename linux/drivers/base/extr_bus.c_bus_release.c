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
struct subsys_private {struct bus_type* bus; } ;
struct kobject {int dummy; } ;
struct bus_type {int /*<<< orphan*/ * p; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct subsys_private*) ; 
 struct subsys_private* to_subsys_private (struct kobject*) ; 

__attribute__((used)) static void bus_release(struct kobject *kobj)
{
	struct subsys_private *priv = to_subsys_private(kobj);
	struct bus_type *bus = priv->bus;

	kfree(priv);
	bus->p = NULL;
}