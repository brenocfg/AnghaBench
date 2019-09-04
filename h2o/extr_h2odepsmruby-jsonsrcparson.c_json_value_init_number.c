#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double number; } ;
struct TYPE_5__ {TYPE_1__ value; int /*<<< orphan*/  type; int /*<<< orphan*/ * parent; } ;
typedef  TYPE_2__ JSON_Value ;

/* Variables and functions */
 int /*<<< orphan*/  JSONNumber ; 
 scalar_t__ parson_malloc (int) ; 

JSON_Value * json_value_init_number(double number) {
    JSON_Value *new_value = NULL;
    if ((number * 0.0) != 0.0) { /* nan and inf test */
        return NULL;
    }
    new_value = (JSON_Value*)parson_malloc(sizeof(JSON_Value));
    if (new_value == NULL) {
        return NULL;
    }
    new_value->parent = NULL;
    new_value->type = JSONNumber;
    new_value->value.number = number;
    return new_value;
}