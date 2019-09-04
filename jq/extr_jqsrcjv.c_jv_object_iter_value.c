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
typedef  int /*<<< orphan*/  jv ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 TYPE_1__* jvp_object_get_slot (int /*<<< orphan*/ ,int) ; 

jv jv_object_iter_value(jv object, int iter) {
  return jv_copy(jvp_object_get_slot(object, iter)->value);
}