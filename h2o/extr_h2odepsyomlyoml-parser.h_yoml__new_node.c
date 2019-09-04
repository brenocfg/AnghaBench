#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ yoml_type_t ;
struct TYPE_12__ {int _refcnt; int /*<<< orphan*/ * tag; int /*<<< orphan*/ * anchor; int /*<<< orphan*/  column; int /*<<< orphan*/  line; scalar_t__ type; int /*<<< orphan*/ * filename; } ;
typedef  TYPE_4__ yoml_t ;
struct TYPE_11__ {int /*<<< orphan*/  column; int /*<<< orphan*/  line; } ;
struct TYPE_9__ {int style; } ;
struct TYPE_10__ {TYPE_1__ scalar; } ;
struct TYPE_13__ {TYPE_3__ start_mark; TYPE_2__ data; } ;
typedef  TYPE_5__ yaml_event_t ;
typedef  int /*<<< orphan*/  yaml_char_t ;

/* Variables and functions */
#define  YAML_FOLDED_SCALAR_STYLE 129 
#define  YAML_LITERAL_SCALAR_STYLE 128 
 scalar_t__ YOML_TYPE_SCALAR ; 
 TYPE_4__* malloc (size_t) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int /*<<< orphan*/ * yoml__strdup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline yoml_t *yoml__new_node(const char *filename, yoml_type_t type, size_t sz, yaml_char_t *anchor, yaml_char_t *tag, yaml_event_t *event)
{
    yoml_t *node = malloc(sz);
    node->filename = filename != NULL ? strdup(filename) : NULL;
    node->type = type;
    node->line = event->start_mark.line;
    if (type == YOML_TYPE_SCALAR) {
        switch (event->data.scalar.style) {
        case YAML_LITERAL_SCALAR_STYLE:
        case YAML_FOLDED_SCALAR_STYLE:
            ++node->line;
            break;
        default:
            break;
        }
    }
    node->column = event->start_mark.column;
    node->anchor = anchor != NULL ? yoml__strdup(anchor) : NULL;
    node->tag = tag != NULL ? yoml__strdup(tag) : NULL;
    node->_refcnt = 1;
    return node;
}