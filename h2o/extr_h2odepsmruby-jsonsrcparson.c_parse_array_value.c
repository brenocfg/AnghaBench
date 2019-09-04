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
typedef  int /*<<< orphan*/  JSON_Array ;

/* Variables and functions */
 scalar_t__ JSONFailure ; 
 int /*<<< orphan*/  SKIP_CHAR (char const**) ; 
 int /*<<< orphan*/  SKIP_WHITESPACES (char const**) ; 
 scalar_t__ json_array_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_array_get_count (int /*<<< orphan*/ *) ; 
 scalar_t__ json_array_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_value_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_value_get_array (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_value_init_array () ; 
 int /*<<< orphan*/ * parse_value (char const**,size_t) ; 

__attribute__((used)) static JSON_Value * parse_array_value(const char **string, size_t nesting) {
    JSON_Value *output_value = json_value_init_array(), *new_array_value = NULL;
    JSON_Array *output_array = json_value_get_array(output_value);
    if (!output_value || **string != '[') {
        return NULL;
    }
    SKIP_CHAR(string);
    SKIP_WHITESPACES(string);
    if (**string == ']') { /* empty array */
        SKIP_CHAR(string);
        return output_value;
    }
    while (**string != '\0') {
        new_array_value = parse_value(string, nesting);
        if (new_array_value == NULL) {
            json_value_free(output_value);
            return NULL;
        }
        if (json_array_add(output_array, new_array_value) == JSONFailure) {
            json_value_free(new_array_value);
            json_value_free(output_value);
            return NULL;
        }
        SKIP_WHITESPACES(string);
        if (**string != ',') {
            break;
        }
        SKIP_CHAR(string);
        SKIP_WHITESPACES(string);
    }
    SKIP_WHITESPACES(string);
    if (**string != ']' || /* Trim array after parsing is over */
        json_array_resize(output_array, json_array_get_count(output_array)) == JSONFailure) {
            json_value_free(output_value);
            return NULL;
    }
    SKIP_CHAR(string);
    return output_value;
}