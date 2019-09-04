#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  array; TYPE_2__* string; int /*<<< orphan*/  object; } ;
struct TYPE_7__ {TYPE_1__ value; } ;
typedef  TYPE_2__ JSON_Value ;

/* Variables and functions */
#define  JSONArray 130 
#define  JSONObject 129 
#define  JSONString 128 
 int /*<<< orphan*/  json_array_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_object_free (int /*<<< orphan*/ ) ; 
 int json_value_get_type (TYPE_2__*) ; 
 int /*<<< orphan*/  parson_free (TYPE_2__*) ; 

void json_value_free(JSON_Value *value) {
    switch (json_value_get_type(value)) {
        case JSONObject:
            json_object_free(value->value.object);
            break;
        case JSONString:
            parson_free(value->value.string);
            break;
        case JSONArray:
            json_array_free(value->value.array);
            break;
        default:
            break;
    }
    parson_free(value);
}