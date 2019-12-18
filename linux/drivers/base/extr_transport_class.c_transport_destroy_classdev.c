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
struct transport_class {scalar_t__ remove; } ;
struct device {int dummy; } ;
struct attribute_container {int /*<<< orphan*/  class; } ;

/* Variables and functions */
 scalar_t__ anon_transport_dummy_function ; 
 struct transport_class* class_to_transport_class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

__attribute__((used)) static void transport_destroy_classdev(struct attribute_container *cont,
				      struct device *dev,
				      struct device *classdev)
{
	struct transport_class *tclass = class_to_transport_class(cont->class);

	if (tclass->remove != anon_transport_dummy_function)
		put_device(classdev);
}