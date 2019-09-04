#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
typedef  TYPE_1__ JSON_Value ;
typedef  int /*<<< orphan*/  JSON_Status ;
typedef  int /*<<< orphan*/  JSON_Array ;

/* Variables and functions */
 int /*<<< orphan*/  JSONFailure ; 
 int /*<<< orphan*/  json_array_add (int /*<<< orphan*/ *,TYPE_1__*) ; 

JSON_Status json_array_append_value(JSON_Array *array, JSON_Value *value) {
    if (array == NULL || value == NULL || value->parent != NULL) {
        return JSONFailure;
    }
    return json_array_add(array, value);
}