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
typedef  int /*<<< orphan*/  JSON_Value ;
typedef  scalar_t__ JSON_Status ;
typedef  int /*<<< orphan*/  JSON_Array ;

/* Variables and functions */
 scalar_t__ JSONFailure ; 
 scalar_t__ JSONSuccess ; 
 scalar_t__ json_array_replace_value (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_value_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_value_init_null () ; 

JSON_Status json_array_replace_null(JSON_Array *array, size_t i) {
    JSON_Value *value = json_value_init_null();
    if (value == NULL) {
        return JSONFailure;
    }
    if (json_array_replace_value(array, i, value) == JSONFailure) {
        json_value_free(value);
        return JSONFailure;
    }
    return JSONSuccess;
}