#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int count; scalar_t__ items; } ;
typedef  int /*<<< orphan*/  JSON_Value ;
typedef  int /*<<< orphan*/  JSON_Status ;
typedef  TYPE_1__ JSON_Array ;

/* Variables and functions */
 int /*<<< orphan*/  JSONFailure ; 
 int /*<<< orphan*/  JSONSuccess ; 
 int json_array_get_count (TYPE_1__*) ; 
 int /*<<< orphan*/  json_array_get_value (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  json_value_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,size_t) ; 

JSON_Status json_array_remove(JSON_Array *array, size_t ix) {
    size_t to_move_bytes = 0;
    if (array == NULL || ix >= json_array_get_count(array)) {
        return JSONFailure;
    }
    json_value_free(json_array_get_value(array, ix));
    to_move_bytes = (json_array_get_count(array) - 1 - ix) * sizeof(JSON_Value*);
    memmove(array->items + ix, array->items + ix + 1, to_move_bytes);
    array->count -= 1;
    return JSONSuccess;
}