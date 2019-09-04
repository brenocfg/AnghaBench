#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__** values; int /*<<< orphan*/ * names; } ;
struct TYPE_12__ {int /*<<< orphan*/ * parent; } ;
typedef  TYPE_1__ JSON_Value ;
typedef  int /*<<< orphan*/  JSON_Status ;
typedef  TYPE_2__ JSON_Object ;

/* Variables and functions */
 int /*<<< orphan*/  JSONFailure ; 
 int /*<<< orphan*/  JSONSuccess ; 
 int /*<<< orphan*/  json_object_add (TYPE_2__*,char const*,TYPE_1__*) ; 
 size_t json_object_get_count (TYPE_2__*) ; 
 TYPE_1__* json_object_get_value (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/ * json_object_get_wrapping_value (TYPE_2__*) ; 
 int /*<<< orphan*/  json_value_free (TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

JSON_Status json_object_set_value(JSON_Object *object, const char *name, JSON_Value *value) {
    size_t i = 0;
    JSON_Value *old_value;
    if (object == NULL || name == NULL || value == NULL || value->parent != NULL) {
        return JSONFailure;
    }
    old_value = json_object_get_value(object, name);
    if (old_value != NULL) { /* free and overwrite old value */
        json_value_free(old_value);
        for (i = 0; i < json_object_get_count(object); i++) {
            if (strcmp(object->names[i], name) == 0) {
                value->parent = json_object_get_wrapping_value(object);
                object->values[i] = value;
                return JSONSuccess;
            }
        }
    }
    /* add new key value pair */
    return json_object_add(object, name, value);
}