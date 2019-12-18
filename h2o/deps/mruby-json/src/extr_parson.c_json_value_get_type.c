#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  JSON_Value_Type ;
typedef  TYPE_1__ JSON_Value ;

/* Variables and functions */
 int /*<<< orphan*/  JSONError ; 

JSON_Value_Type json_value_get_type(const JSON_Value *value) {
    return value ? value->type : JSONError;
}