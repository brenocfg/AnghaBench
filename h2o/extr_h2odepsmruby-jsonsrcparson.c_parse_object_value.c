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
typedef  int /*<<< orphan*/  JSON_Object ;

/* Variables and functions */
 scalar_t__ JSONFailure ; 
 int /*<<< orphan*/  SKIP_CHAR (char const**) ; 
 int /*<<< orphan*/  SKIP_WHITESPACES (char const**) ; 
 char* get_quoted_string (char const**) ; 
 scalar_t__ json_object_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_object_get_count (int /*<<< orphan*/ *) ; 
 scalar_t__ json_object_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_value_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_value_get_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_value_init_object () ; 
 int /*<<< orphan*/ * parse_value (char const**,size_t) ; 
 int /*<<< orphan*/  parson_free (char*) ; 

__attribute__((used)) static JSON_Value * parse_object_value(const char **string, size_t nesting) {
    JSON_Value *output_value = json_value_init_object(), *new_value = NULL;
    JSON_Object *output_object = json_value_get_object(output_value);
    char *new_key = NULL;
    if (output_value == NULL || **string != '{') {
        return NULL;
    }
    SKIP_CHAR(string);
    SKIP_WHITESPACES(string);
    if (**string == '}') { /* empty object */
        SKIP_CHAR(string);
        return output_value;
    }
    while (**string != '\0') {
        new_key = get_quoted_string(string);
        if (new_key == NULL) {
            json_value_free(output_value);
            return NULL;
        }
        SKIP_WHITESPACES(string);
        if (**string != ':') {
            parson_free(new_key);
            json_value_free(output_value);
            return NULL;
        }
        SKIP_CHAR(string);
        new_value = parse_value(string, nesting);
        if (new_value == NULL) {
            parson_free(new_key);
            json_value_free(output_value);
            return NULL;
        }
        if (json_object_add(output_object, new_key, new_value) == JSONFailure) {
            parson_free(new_key);
            json_value_free(new_value);
            json_value_free(output_value);
            return NULL;
        }
        parson_free(new_key);
        SKIP_WHITESPACES(string);
        if (**string != ',') {
            break;
        }
        SKIP_CHAR(string);
        SKIP_WHITESPACES(string);
    }
    SKIP_WHITESPACES(string);
    if (**string != '}' || /* Trim object after parsing is over */
        json_object_resize(output_object, json_object_get_count(output_object)) == JSONFailure) {
            json_value_free(output_value);
            return NULL;
    }
    SKIP_CHAR(string);
    return output_value;
}