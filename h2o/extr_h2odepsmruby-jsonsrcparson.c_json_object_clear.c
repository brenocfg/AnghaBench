#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ count; int /*<<< orphan*/ * values; int /*<<< orphan*/ * names; } ;
typedef  int /*<<< orphan*/  JSON_Status ;
typedef  TYPE_1__ JSON_Object ;

/* Variables and functions */
 int /*<<< orphan*/  JSONFailure ; 
 int /*<<< orphan*/  JSONSuccess ; 
 size_t json_object_get_count (TYPE_1__*) ; 
 int /*<<< orphan*/  json_value_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parson_free (int /*<<< orphan*/ ) ; 

JSON_Status json_object_clear(JSON_Object *object) {
    size_t i = 0;
    if (object == NULL) {
        return JSONFailure;
    }
    for (i = 0; i < json_object_get_count(object); i++) {
        parson_free(object->names[i]);
        json_value_free(object->values[i]);
    }
    object->count = 0;
    return JSONSuccess;
}