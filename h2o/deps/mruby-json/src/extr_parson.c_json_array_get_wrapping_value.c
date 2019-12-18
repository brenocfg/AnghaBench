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
struct TYPE_3__ {int /*<<< orphan*/ * wrapping_value; } ;
typedef  int /*<<< orphan*/  JSON_Value ;
typedef  TYPE_1__ JSON_Array ;

/* Variables and functions */

JSON_Value * json_array_get_wrapping_value(const JSON_Array *array) {
    return array->wrapping_value;
}