#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t size; } ;
typedef  TYPE_1__ jv ;
struct TYPE_6__ {int /*<<< orphan*/ * elements; } ;

/* Variables and functions */
 TYPE_2__* jvp_object_ptr (TYPE_1__) ; 

__attribute__((used)) static int* jvp_object_buckets(jv o) {
  return (int*)(&jvp_object_ptr(o)->elements[o.size]);
}