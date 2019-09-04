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
typedef  int /*<<< orphan*/  JSON_Object ;

/* Variables and functions */
 int /*<<< orphan*/ * json_value_get_object (int /*<<< orphan*/  const*) ; 

JSON_Object * json_object (const JSON_Value *value) {
    return json_value_get_object(value);
}