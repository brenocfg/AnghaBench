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
 scalar_t__ JSONSuccess ; 
 scalar_t__ json_object_dotset_value (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_value_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_value_init_number (double) ; 

JSON_Status json_object_dotset_number(JSON_Object *object, const char *name, double number) {
    JSON_Value *value = json_value_init_number(number);
    if (value == NULL) {
        return JSONFailure;
    }
    if (json_object_dotset_value(object, name, value) == JSONFailure) {
        json_value_free(value);
        return JSONFailure;
    }
    return JSONSuccess;
}