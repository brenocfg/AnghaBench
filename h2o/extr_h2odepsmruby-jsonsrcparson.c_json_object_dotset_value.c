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
typedef  int /*<<< orphan*/  JSON_Object ;

/* Variables and functions */
 scalar_t__ JSONFailure ; 
 scalar_t__ json_object_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_object_get_object (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ json_object_set_value (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_value_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_value_init_object () ; 
 int /*<<< orphan*/  parson_free (char*) ; 
 char* parson_strndup (char const*,int) ; 
 char* strchr (char const*,char) ; 

JSON_Status json_object_dotset_value(JSON_Object *object, const char *name, JSON_Value *value) {
    const char *dot_pos = NULL;
    char *current_name = NULL;
    JSON_Object *temp_obj = NULL;
    JSON_Value *new_value = NULL;
    if (object == NULL || name == NULL || value == NULL) {
        return JSONFailure;
    }
    dot_pos = strchr(name, '.');
    if (dot_pos == NULL) {
        return json_object_set_value(object, name, value);
    } else {
        current_name = parson_strndup(name, dot_pos - name);
        temp_obj = json_object_get_object(object, current_name);
        if (temp_obj == NULL) {
            new_value = json_value_init_object();
            if (new_value == NULL) {
                parson_free(current_name);
                return JSONFailure;
            }
            if (json_object_add(object, current_name, new_value) == JSONFailure) {
                json_value_free(new_value);
                parson_free(current_name);
                return JSONFailure;
            }
            temp_obj = json_object_get_object(object, current_name);
        }
        parson_free(current_name);
        return json_object_dotset_value(temp_obj, dot_pos + 1, value);
    }
}