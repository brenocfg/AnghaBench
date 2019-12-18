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
typedef  double intmax_t ;
typedef  int /*<<< orphan*/  JSON_Value ;
typedef  int /*<<< orphan*/  JSON_Object ;
typedef  int /*<<< orphan*/  JSON_Array ;

/* Variables and functions */
 int /*<<< orphan*/  APPEND_INDENT (int) ; 
 int /*<<< orphan*/  APPEND_STRING (char*) ; 
 char* FIXED_FORMAT ; 
 char* FLOAT_FORMAT ; 
#define  JSONArray 135 
#define  JSONBoolean 134 
#define  JSONError 133 
#define  JSONFixed 132 
#define  JSONNull 131 
#define  JSONNumber 130 
#define  JSONObject 129 
#define  JSONString 128 
 size_t json_array_get_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_array_get_value (int /*<<< orphan*/ *,size_t) ; 
 size_t json_object_get_count (int /*<<< orphan*/ *) ; 
 char* json_object_get_name (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * json_object_get_value (int /*<<< orphan*/ *,char const*) ; 
 int json_serialize_string (char const*,char*) ; 
 int /*<<< orphan*/ * json_value_get_array (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  json_value_get_boolean (int /*<<< orphan*/  const*) ; 
 double json_value_get_fixed (int /*<<< orphan*/  const*) ; 
 double json_value_get_number (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * json_value_get_object (int /*<<< orphan*/  const*) ; 
 char* json_value_get_string (int /*<<< orphan*/  const*) ; 
 int json_value_get_type (int /*<<< orphan*/  const*) ; 
 int sprintf (char*,char*,double) ; 

__attribute__((used)) static int json_serialize_to_buffer_r(const JSON_Value *value, char *buf, int level, int is_pretty, char *num_buf)
{
    const char *key = NULL, *string = NULL;
    JSON_Value *temp_value = NULL;
    JSON_Array *array = NULL;
    JSON_Object *object = NULL;
    size_t i = 0, count = 0;
    double num = 0.0;
#ifdef JSON_FIXED_NUMBER
    intmax_t inum = 0;
#endif
    int written = -1, written_total = 0;

    switch (json_value_get_type(value)) {
        case JSONArray:
            array = json_value_get_array(value);
            count = json_array_get_count(array);
            APPEND_STRING("[");
            if (count > 0 && is_pretty) {
                APPEND_STRING("\n");
            }
            for (i = 0; i < count; i++) {
                if (is_pretty) {
                    APPEND_INDENT(level+1);
                }
                temp_value = json_array_get_value(array, i);
                written = json_serialize_to_buffer_r(temp_value, buf, level+1, is_pretty, num_buf);
                if (written < 0) {
                    return -1;
                }
                if (buf != NULL) {
                    buf += written;
                }
                written_total += written;
                if (i < (count - 1)) {
                    APPEND_STRING(",");
                }
                if (is_pretty) {
                    APPEND_STRING("\n");
                }
            }
            if (count > 0 && is_pretty) {
                APPEND_INDENT(level);
            }
            APPEND_STRING("]");
            return written_total;
        case JSONObject:
            object = json_value_get_object(value);
            count  = json_object_get_count(object);
            APPEND_STRING("{");
            if (count > 0 && is_pretty) {
                APPEND_STRING("\n");
            }
            for (i = 0; i < count; i++) {
                key = json_object_get_name(object, i);
                if (key == NULL) {
                    return -1;
                }
                if (is_pretty) {
                    APPEND_INDENT(level+1);
                }
                written = json_serialize_string(key, buf);
                if (written < 0) {
                    return -1;
                }
                if (buf != NULL) {
                    buf += written;
                }
                written_total += written;
                APPEND_STRING(":");
                if (is_pretty) {
                    APPEND_STRING(" ");
                }
                temp_value = json_object_get_value(object, key);
                written = json_serialize_to_buffer_r(temp_value, buf, level+1, is_pretty, num_buf);
                if (written < 0) {
                    return -1;
                }
                if (buf != NULL) {
                    buf += written;
                }
                written_total += written;
                if (i < (count - 1)) {
                    APPEND_STRING(",");
                }
                if (is_pretty) {
                    APPEND_STRING("\n");
                }
            }
            if (count > 0 && is_pretty) {
                APPEND_INDENT(level);
            }
            APPEND_STRING("}");
            return written_total;
        case JSONString:
            string = json_value_get_string(value);
            if (string == NULL) {
                return -1;
            }
            written = json_serialize_string(string, buf);
            if (written < 0) {
                return -1;
            }
            if (buf != NULL) {
                buf += written;
            }
            written_total += written;
            return written_total;
        case JSONBoolean:
            if (json_value_get_boolean(value)) {
                APPEND_STRING("true");
            } else {
                APPEND_STRING("false");
            }
            return written_total;
#ifdef JSON_FIXED_NUMBER
        case JSONFixed:
            inum = json_value_get_fixed(value);
            if (buf != NULL) {
                num_buf = buf;
            }
            written = sprintf(num_buf, FIXED_FORMAT, inum);
            if (written < 0) {
                return -1;
            }
            if (buf != NULL) {
                buf += written;
            }
            written_total += written;
            return written_total;
#endif
        case JSONNumber:
            num = json_value_get_number(value);
            if (buf != NULL) {
                num_buf = buf;
            }
            written = sprintf(num_buf, FLOAT_FORMAT, num);
            if (written < 0) {
                return -1;
            }
            if (buf != NULL) {
                buf += written;
            }
            written_total += written;
            return written_total;
        case JSONNull:
            APPEND_STRING("null");
            return written_total;
        case JSONError:
            return -1;
        default:
            return -1;
    }
}