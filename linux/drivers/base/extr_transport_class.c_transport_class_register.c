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
struct transport_class {int /*<<< orphan*/  class; } ;

/* Variables and functions */
 int class_register (int /*<<< orphan*/ *) ; 

int transport_class_register(struct transport_class *tclass)
{
	return class_register(&tclass->class);
}