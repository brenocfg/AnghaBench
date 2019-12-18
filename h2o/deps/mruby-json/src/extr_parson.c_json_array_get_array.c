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
typedef  int /*<<< orphan*/  JSON_Array ;

/* Variables and functions */
 int /*<<< orphan*/  json_array_get_value (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/ * json_value_get_array (int /*<<< orphan*/ ) ; 

JSON_Array * json_array_get_array(const JSON_Array *array, size_t index) {
    return json_value_get_array(json_array_get_value(array, index));
}