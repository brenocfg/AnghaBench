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
struct TYPE_3__ {int count; size_t capacity; int /*<<< orphan*/ ** items; } ;
typedef  int /*<<< orphan*/  JSON_Value ;
typedef  int /*<<< orphan*/  JSON_Status ;
typedef  TYPE_1__ JSON_Array ;

/* Variables and functions */
 int /*<<< orphan*/  JSONFailure ; 
 int /*<<< orphan*/  JSONSuccess ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  parson_free (int /*<<< orphan*/ **) ; 
 scalar_t__ parson_malloc (size_t) ; 

__attribute__((used)) static JSON_Status json_array_resize(JSON_Array *array, size_t new_capacity) {
    JSON_Value **new_items = NULL;
    if (new_capacity == 0) {
        return JSONFailure;
    }
    new_items = (JSON_Value**)parson_malloc(new_capacity * sizeof(JSON_Value*));
    if (new_items == NULL) {
        return JSONFailure;
    }
    if (array->items != NULL && array->count > 0) {
        memcpy(new_items, array->items, array->count * sizeof(JSON_Value*));
    }
    parson_free(array->items);
    array->items = new_items;
    array->capacity = new_capacity;
    return JSONSuccess;
}