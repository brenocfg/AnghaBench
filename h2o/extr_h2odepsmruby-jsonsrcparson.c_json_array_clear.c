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
struct TYPE_5__ {scalar_t__ count; } ;
typedef  int /*<<< orphan*/  JSON_Status ;
typedef  TYPE_1__ JSON_Array ;

/* Variables and functions */
 int /*<<< orphan*/  JSONFailure ; 
 int /*<<< orphan*/  JSONSuccess ; 
 size_t json_array_get_count (TYPE_1__*) ; 
 int /*<<< orphan*/  json_array_get_value (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  json_value_free (int /*<<< orphan*/ ) ; 

JSON_Status json_array_clear(JSON_Array *array) {
    size_t i = 0;
    if (array == NULL) {
        return JSONFailure;
    }
    for (i = 0; i < json_array_get_count(array); i++) {
        json_value_free(json_array_get_value(array, i));
    }
    array->count = 0;
    return JSONSuccess;
}