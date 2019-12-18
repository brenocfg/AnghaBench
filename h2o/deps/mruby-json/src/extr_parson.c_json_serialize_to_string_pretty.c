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

/* Variables and functions */
 scalar_t__ JSONFailure ; 
 int /*<<< orphan*/  json_free_serialized_string (char*) ; 
 size_t json_serialization_size_pretty (int /*<<< orphan*/  const*) ; 
 scalar_t__ json_serialize_to_buffer_pretty (int /*<<< orphan*/  const*,char*,size_t) ; 
 scalar_t__ parson_malloc (size_t) ; 

char * json_serialize_to_string_pretty(const JSON_Value *value) {
    JSON_Status serialization_result = JSONFailure;
    size_t buf_size_bytes = json_serialization_size_pretty(value);
    char *buf = NULL;
    if (buf_size_bytes == 0) {
        return NULL;
    }
    buf = (char*)parson_malloc(buf_size_bytes);
    if (buf == NULL) {
        return NULL;
    }
    serialization_result = json_serialize_to_buffer_pretty(value, buf, buf_size_bytes);
    if (serialization_result == JSONFailure) {
        json_free_serialized_string(buf);
        return NULL;
    }
    return buf;
}