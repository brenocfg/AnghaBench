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
struct TYPE_9__ {int count; int capacity; TYPE_1__** values; int /*<<< orphan*/ ** names; } ;
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
typedef  TYPE_1__ JSON_Value ;
typedef  scalar_t__ JSON_Status ;
typedef  TYPE_2__ JSON_Object ;

/* Variables and functions */
 scalar_t__ JSONFailure ; 
 scalar_t__ JSONSuccess ; 
 size_t MAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STARTING_CAPACITY ; 
 int /*<<< orphan*/ * json_object_get_value (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  json_object_get_wrapping_value (TYPE_2__*) ; 
 scalar_t__ json_object_resize (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/ * parson_strdup (char const*) ; 

__attribute__((used)) static JSON_Status json_object_add(JSON_Object *object, const char *name, JSON_Value *value) {
    size_t index = 0;
    if (object == NULL || name == NULL || value == NULL) {
        return JSONFailure;
    }
    if (json_object_get_value(object, name) != NULL) {
        return JSONFailure;
    }
    if (object->count >= object->capacity) {
        size_t new_capacity = MAX(object->capacity * 2, STARTING_CAPACITY);
        if (json_object_resize(object, new_capacity) == JSONFailure) {
            return JSONFailure;
        }
    }
    index = object->count;
    object->names[index] = parson_strdup(name);
    if (object->names[index] == NULL) {
        return JSONFailure;
    }
    value->parent = json_object_get_wrapping_value(object);
    object->values[index] = value;
    object->count++;
    return JSONSuccess;
}