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
typedef  int /*<<< orphan*/  JSON_Object ;

/* Variables and functions */
 int /*<<< orphan*/  json_object_dotget_value (int /*<<< orphan*/  const*,char const*) ; 
 int json_value_get_boolean (int /*<<< orphan*/ ) ; 

int json_object_dotget_boolean(const JSON_Object *object, const char *name) {
    return json_value_get_boolean(json_object_dotget_value(object, name));
}