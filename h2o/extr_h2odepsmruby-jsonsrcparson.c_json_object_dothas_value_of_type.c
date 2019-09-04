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
typedef  scalar_t__ JSON_Value_Type ;
typedef  int /*<<< orphan*/  JSON_Value ;
typedef  int /*<<< orphan*/  JSON_Object ;

/* Variables and functions */
 int /*<<< orphan*/ * json_object_dotget_value (int /*<<< orphan*/  const*,char const*) ; 
 scalar_t__ json_value_get_type (int /*<<< orphan*/ *) ; 

int json_object_dothas_value_of_type(const JSON_Object *object, const char *name, JSON_Value_Type type) {
    JSON_Value *val = json_object_dotget_value(object, name);
    return val != NULL && json_value_get_type(val) == type;
}