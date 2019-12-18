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
struct TYPE_2__ {int /*<<< orphan*/  class_instance; int /*<<< orphan*/  class_class; } ;
typedef  TYPE_1__ trayclient ;

/* Variables and functions */
 int strcasecmp_nullable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reorder_trayclients_cmp(const void *_a, const void *_b) {
    trayclient *a = *((trayclient **)_a);
    trayclient *b = *((trayclient **)_b);

    int result = strcasecmp_nullable(a->class_class, b->class_class);
    return result != 0 ? result : strcasecmp_nullable(a->class_instance, b->class_instance);
}