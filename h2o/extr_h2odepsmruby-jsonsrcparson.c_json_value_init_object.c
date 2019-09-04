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
struct TYPE_6__ {int /*<<< orphan*/  object; } ;
struct TYPE_7__ {TYPE_1__ value; int /*<<< orphan*/  type; int /*<<< orphan*/ * parent; } ;
typedef  TYPE_2__ JSON_Value ;

/* Variables and functions */
 int /*<<< orphan*/  JSONObject ; 
 int /*<<< orphan*/  json_object_init (TYPE_2__*) ; 
 int /*<<< orphan*/  parson_free (TYPE_2__*) ; 
 scalar_t__ parson_malloc (int) ; 

JSON_Value * json_value_init_object(void) {
    JSON_Value *new_value = (JSON_Value*)parson_malloc(sizeof(JSON_Value));
    if (!new_value) {
        return NULL;
    }
    new_value->parent = NULL;
    new_value->type = JSONObject;
    new_value->value.object = json_object_init(new_value);
    if (!new_value->value.object) {
        parson_free(new_value);
        return NULL;
    }
    return new_value;
}