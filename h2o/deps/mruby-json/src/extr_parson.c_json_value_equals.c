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
typedef  int JSON_Value_Type ;
typedef  int /*<<< orphan*/  JSON_Value ;
typedef  int /*<<< orphan*/  JSON_Object ;
typedef  int /*<<< orphan*/  JSON_Array ;

/* Variables and functions */
#define  JSONArray 135 
#define  JSONBoolean 134 
#define  JSONError 133 
#define  JSONFixed 132 
#define  JSONNull 131 
#define  JSONNumber 130 
#define  JSONObject 129 
#define  JSONString 128 
 double fabs (scalar_t__) ; 
 size_t json_array_get_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_array_get_value (int /*<<< orphan*/ *,size_t) ; 
 size_t json_object_get_count (int /*<<< orphan*/ *) ; 
 char* json_object_get_name (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * json_object_get_value (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * json_value_get_array (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  json_value_get_boolean (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  json_value_get_fixed (int /*<<< orphan*/  const*) ; 
 scalar_t__ json_value_get_number (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * json_value_get_object (int /*<<< orphan*/  const*) ; 
 char* json_value_get_string (int /*<<< orphan*/  const*) ; 
 int json_value_get_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

int json_value_equals(const JSON_Value *a, const JSON_Value *b) {
    JSON_Object *a_object = NULL, *b_object = NULL;
    JSON_Array *a_array = NULL, *b_array = NULL;
    const char *a_string = NULL, *b_string = NULL;
    const char *key = NULL;
    size_t a_count = 0, b_count = 0, i = 0;
    JSON_Value_Type a_type, b_type;
    a_type = json_value_get_type(a);
    b_type = json_value_get_type(b);
    if (a_type != b_type) {
        return 0;
    }
    switch (a_type) {
        case JSONArray:
            a_array = json_value_get_array(a);
            b_array = json_value_get_array(b);
            a_count = json_array_get_count(a_array);
            b_count = json_array_get_count(b_array);
            if (a_count != b_count) {
                return 0;
            }
            for (i = 0; i < a_count; i++) {
                if (!json_value_equals(json_array_get_value(a_array, i),
                                       json_array_get_value(b_array, i))) {
                    return 0;
                }
            }
            return 1;
        case JSONObject:
            a_object = json_value_get_object(a);
            b_object = json_value_get_object(b);
            a_count = json_object_get_count(a_object);
            b_count = json_object_get_count(b_object);
            if (a_count != b_count) {
                return 0;
            }
            for (i = 0; i < a_count; i++) {
                key = json_object_get_name(a_object, i);
                if (!json_value_equals(json_object_get_value(a_object, key),
                                       json_object_get_value(b_object, key))) {
                    return 0;
                }
            }
            return 1;
        case JSONString:
            a_string = json_value_get_string(a);
            b_string = json_value_get_string(b);
            if (a_string == NULL || b_string == NULL) {
                return 0; /* shouldn't happen */
            }
            return strcmp(a_string, b_string) == 0;
        case JSONBoolean:
            return json_value_get_boolean(a) == json_value_get_boolean(b);
        case JSONNumber:
            return fabs(json_value_get_number(a) - json_value_get_number(b)) < 0.000001; /* EPSILON */
#ifdef JSON_FIXED_NUMBER
        case JSONFixed:
            return json_value_get_fixed(a) == json_value_get_fixed(b);
#endif
        case JSONError:
            return 1;
        case JSONNull:
            return 1;
        default:
            return 1;
    }
}