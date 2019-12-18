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
typedef  int /*<<< orphan*/  const JSON_Value ;
typedef  int /*<<< orphan*/  JSON_Object ;
typedef  int /*<<< orphan*/  JSON_Array ;

/* Variables and functions */
#define  JSONArray 135 
#define  JSONBoolean 134 
#define  JSONError 133 
 int /*<<< orphan*/  JSONFailure ; 
#define  JSONFixed 132 
#define  JSONNull 131 
#define  JSONNumber 130 
#define  JSONObject 129 
#define  JSONString 128 
 int /*<<< orphan*/  json_array_add (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 size_t json_array_get_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* json_array_get_value (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  json_object_add (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*) ; 
 size_t json_object_get_count (int /*<<< orphan*/ *) ; 
 char* json_object_get_name (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  const* json_object_get_value (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  json_value_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * json_value_get_array (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  json_value_get_boolean (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  json_value_get_fixed (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  json_value_get_number (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * json_value_get_object (int /*<<< orphan*/  const*) ; 
 char* json_value_get_string (int /*<<< orphan*/  const*) ; 
 int json_value_get_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* json_value_init_array () ; 
 int /*<<< orphan*/  const* json_value_init_boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* json_value_init_fixed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* json_value_init_null () ; 
 int /*<<< orphan*/  const* json_value_init_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* json_value_init_object () ; 
 int /*<<< orphan*/  const* json_value_init_string_no_copy (char*) ; 
 int /*<<< orphan*/  parson_free (char*) ; 
 char* parson_strdup (char const*) ; 

JSON_Value * json_value_deep_copy(const JSON_Value *value) {
    size_t i = 0;
    JSON_Value *return_value = NULL, *temp_value_copy = NULL, *temp_value = NULL;
    const char *temp_string = NULL, *temp_key = NULL;
    char *temp_string_copy = NULL;
    JSON_Array *temp_array = NULL, *temp_array_copy = NULL;
    JSON_Object *temp_object = NULL, *temp_object_copy = NULL;

    switch (json_value_get_type(value)) {
        case JSONArray:
            temp_array = json_value_get_array(value);
            return_value = json_value_init_array();
            if (return_value == NULL) {
                return NULL;
            }
            temp_array_copy = json_value_get_array(return_value);
            for (i = 0; i < json_array_get_count(temp_array); i++) {
                temp_value = json_array_get_value(temp_array, i);
                temp_value_copy = json_value_deep_copy(temp_value);
                if (temp_value_copy == NULL) {
                    json_value_free(return_value);
                    return NULL;
                }
                if (json_array_add(temp_array_copy, temp_value_copy) == JSONFailure) {
                    json_value_free(return_value);
                    json_value_free(temp_value_copy);
                    return NULL;
                }
            }
            return return_value;
        case JSONObject:
            temp_object = json_value_get_object(value);
            return_value = json_value_init_object();
            if (return_value == NULL) {
                return NULL;
            }
            temp_object_copy = json_value_get_object(return_value);
            for (i = 0; i < json_object_get_count(temp_object); i++) {
                temp_key = json_object_get_name(temp_object, i);
                temp_value = json_object_get_value(temp_object, temp_key);
                temp_value_copy = json_value_deep_copy(temp_value);
                if (temp_value_copy == NULL) {
                    json_value_free(return_value);
                    return NULL;
                }
                if (json_object_add(temp_object_copy, temp_key, temp_value_copy) == JSONFailure) {
                    json_value_free(return_value);
                    json_value_free(temp_value_copy);
                    return NULL;
                }
            }
            return return_value;
        case JSONBoolean:
            return json_value_init_boolean(json_value_get_boolean(value));
        case JSONNumber:
            return json_value_init_number(json_value_get_number(value));
#ifdef JSON_FIXED_NUMBER
        case JSONFixed:
            return json_value_init_fixed(json_value_get_fixed(value));
#endif
        case JSONString:
            temp_string = json_value_get_string(value);
            if (temp_string == NULL) {
                return NULL;
            }
            temp_string_copy = parson_strdup(temp_string);
            if (temp_string_copy == NULL) {
                return NULL;
            }
            return_value = json_value_init_string_no_copy(temp_string_copy);
            if (return_value == NULL) {
                parson_free(temp_string_copy);
            }
            return return_value;
        case JSONNull:
            return json_value_init_null();
        case JSONError:
            return NULL;
        default:
            return NULL;
    }
}