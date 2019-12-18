#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t size; TYPE_2__* elements; } ;
struct TYPE_8__ {size_t size; TYPE_5__** elements; } ;
struct TYPE_11__ {TYPE_3__ mapping; TYPE_1__ sequence; } ;
struct TYPE_12__ {int type; TYPE_4__ data; int /*<<< orphan*/ * anchor; } ;
typedef  TYPE_5__ yoml_t ;
struct TYPE_9__ {TYPE_5__* value; TYPE_5__* key; } ;

/* Variables and functions */
#define  YOML_TYPE_MAPPING 129 
#define  YOML_TYPE_SEQUENCE 128 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static inline yoml_t *yoml_find_anchor(yoml_t *node, const char *name)
{
    yoml_t *n;
    size_t i;

    if (node->anchor != NULL && strcmp(node->anchor, name) == 0)
        return node;

    switch (node->type) {
    case YOML_TYPE_SEQUENCE:
        for (i = 0; i != node->data.sequence.size; ++i)
            if ((n = yoml_find_anchor(node->data.sequence.elements[i], name)) != NULL)
                return n;
        break;
    case YOML_TYPE_MAPPING:
        for (i = 0; i != node->data.mapping.size; ++i)
            if ((n = yoml_find_anchor(node->data.mapping.elements[i].key, name)) != NULL ||
                (n = yoml_find_anchor(node->data.mapping.elements[i].value, name)) != NULL)
                return n;
        break;
    default:
        break;
    }

    return NULL;
}