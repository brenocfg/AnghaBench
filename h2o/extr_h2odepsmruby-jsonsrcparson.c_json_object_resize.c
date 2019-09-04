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
struct TYPE_3__ {char** names; char** values; int count; size_t capacity; } ;
typedef  char JSON_Value ;
typedef  int /*<<< orphan*/  JSON_Status ;
typedef  TYPE_1__ JSON_Object ;

/* Variables and functions */
 int /*<<< orphan*/  JSONFailure ; 
 int /*<<< orphan*/  JSONSuccess ; 
 int /*<<< orphan*/  memcpy (char**,char**,int) ; 
 int /*<<< orphan*/  parson_free (char**) ; 
 scalar_t__ parson_malloc (size_t) ; 

__attribute__((used)) static JSON_Status json_object_resize(JSON_Object *object, size_t new_capacity) {
    char **temp_names = NULL;
    JSON_Value **temp_values = NULL;

    if ((object->names == NULL && object->values != NULL) ||
        (object->names != NULL && object->values == NULL) ||
        new_capacity == 0) {
            return JSONFailure; /* Shouldn't happen */
    }
    temp_names = (char**)parson_malloc(new_capacity * sizeof(char*));
    if (temp_names == NULL) {
        return JSONFailure;
    }
    temp_values = (JSON_Value**)parson_malloc(new_capacity * sizeof(JSON_Value*));
    if (temp_values == NULL) {
        parson_free(temp_names);
        return JSONFailure;
    }
    if (object->names != NULL && object->values != NULL && object->count > 0) {
        memcpy(temp_names, object->names, object->count * sizeof(char*));
        memcpy(temp_values, object->values, object->count * sizeof(JSON_Value*));
    }
    parson_free(object->names);
    parson_free(object->values);
    object->names = temp_names;
    object->values = temp_values;
    object->capacity = new_capacity;
    return JSONSuccess;
}