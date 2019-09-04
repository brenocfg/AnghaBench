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
struct TYPE_4__ {int /*<<< orphan*/ ** values; int /*<<< orphan*/ * names; } ;
typedef  int /*<<< orphan*/  JSON_Value ;
typedef  TYPE_1__ JSON_Object ;

/* Variables and functions */
 size_t json_object_get_count (TYPE_1__ const*) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static JSON_Value * json_object_nget_value(const JSON_Object *object, const char *name, size_t n) {
    size_t i, name_length;
    for (i = 0; i < json_object_get_count(object); i++) {
        name_length = strlen(object->names[i]);
        if (name_length != n) {
            continue;
        }
        if (strncmp(object->names[i], name, n) == 0) {
            return object->values[i];
        }
    }
    return NULL;
}