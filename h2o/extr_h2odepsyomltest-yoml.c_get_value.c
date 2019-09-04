#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {size_t size; TYPE_2__* elements; } ;
struct TYPE_12__ {TYPE_3__ mapping; } ;
struct TYPE_14__ {TYPE_4__ data; } ;
typedef  TYPE_6__ yoml_t ;
struct TYPE_9__ {int /*<<< orphan*/  scalar; } ;
struct TYPE_13__ {scalar_t__ type; TYPE_1__ data; } ;
struct TYPE_10__ {TYPE_6__* value; TYPE_5__* key; } ;

/* Variables and functions */
 scalar_t__ YOML_TYPE_SCALAR ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static yoml_t *get_value(yoml_t *mapping, const char *key)
{
    size_t i;
    for (i = 0; i != mapping->data.mapping.size; ++i)
        if (mapping->data.mapping.elements[i].key->type == YOML_TYPE_SCALAR &&
            strcmp(mapping->data.mapping.elements[i].key->data.scalar, key) == 0)
            return mapping->data.mapping.elements[i].value;
    return NULL;
}