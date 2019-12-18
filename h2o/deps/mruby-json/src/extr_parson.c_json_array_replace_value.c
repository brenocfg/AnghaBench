#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__** items; } ;
struct TYPE_8__ {int /*<<< orphan*/ * parent; } ;
typedef  TYPE_1__ JSON_Value ;
typedef  int /*<<< orphan*/  JSON_Status ;
typedef  TYPE_2__ JSON_Array ;

/* Variables and functions */
 int /*<<< orphan*/  JSONFailure ; 
 int /*<<< orphan*/  JSONSuccess ; 
 size_t json_array_get_count (TYPE_2__*) ; 
 int /*<<< orphan*/  json_array_get_value (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/ * json_array_get_wrapping_value (TYPE_2__*) ; 
 int /*<<< orphan*/  json_value_free (int /*<<< orphan*/ ) ; 

JSON_Status json_array_replace_value(JSON_Array *array, size_t ix, JSON_Value *value) {
    if (array == NULL || value == NULL || value->parent != NULL || ix >= json_array_get_count(array)) {
        return JSONFailure;
    }
    json_value_free(json_array_get_value(array, ix));
    value->parent = json_array_get_wrapping_value(array);
    array->items[ix] = value;
    return JSONSuccess;
}