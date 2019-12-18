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
struct TYPE_5__ {int count; int /*<<< orphan*/ * values; int /*<<< orphan*/ * names; } ;
typedef  int /*<<< orphan*/  JSON_Status ;
typedef  TYPE_1__ JSON_Object ;

/* Variables and functions */
 int /*<<< orphan*/  JSONFailure ; 
 int /*<<< orphan*/  JSONSuccess ; 
 size_t json_object_get_count (TYPE_1__*) ; 
 int /*<<< orphan*/ * json_object_get_value (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  json_value_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parson_free (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

JSON_Status json_object_remove(JSON_Object *object, const char *name) {
    size_t i = 0, last_item_index = 0;
    if (object == NULL || json_object_get_value(object, name) == NULL) {
        return JSONFailure;
    }
    last_item_index = json_object_get_count(object) - 1;
    for (i = 0; i < json_object_get_count(object); i++) {
        if (strcmp(object->names[i], name) == 0) {
            parson_free(object->names[i]);
            json_value_free(object->values[i]);
            if (i != last_item_index) { /* Replace key value pair with one from the end */
                object->names[i] = object->names[last_item_index];
                object->values[i] = object->values[last_item_index];
            }
            object->count -= 1;
            return JSONSuccess;
        }
    }
    return JSONFailure; /* No execution path should end here */
}