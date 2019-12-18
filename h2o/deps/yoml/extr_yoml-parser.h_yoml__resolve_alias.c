#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {size_t size; TYPE_2__* elements; } ;
struct TYPE_16__ {size_t size; int /*<<< orphan*/  elements; } ;
struct TYPE_19__ {int /*<<< orphan*/  alias; TYPE_3__ mapping; TYPE_1__ sequence; } ;
struct TYPE_21__ {int type; int /*<<< orphan*/  _refcnt; int /*<<< orphan*/  column; int /*<<< orphan*/  line; TYPE_4__ data; } ;
typedef  TYPE_6__ yoml_t ;
struct TYPE_22__ {int /*<<< orphan*/  mem_set; } ;
typedef  TYPE_7__ yoml_parse_args_t ;
struct TYPE_20__ {int /*<<< orphan*/  column; int /*<<< orphan*/  line; } ;
struct TYPE_23__ {char* problem; TYPE_5__ problem_mark; } ;
typedef  TYPE_8__ yaml_parser_t ;
struct TYPE_17__ {TYPE_6__* value; TYPE_6__* key; } ;

/* Variables and functions */
#define  YOML_TYPE_MAPPING 131 
#define  YOML_TYPE_SCALAR 130 
#define  YOML_TYPE_SEQUENCE 129 
#define  YOML__TYPE_UNRESOLVED_ALIAS 128 
 TYPE_6__* yoml_find_anchor (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yoml_free (TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int yoml__resolve_alias(yoml_t **target, yoml_t *doc, yaml_parser_t *parser, yoml_parse_args_t *parse_args)
{
    size_t i;

    switch ((*target)->type) {
    case YOML_TYPE_SCALAR:
        break;
    case YOML_TYPE_SEQUENCE:
        for (i = 0; i != (*target)->data.sequence.size; ++i) {
            if (yoml__resolve_alias((*target)->data.sequence.elements + i, doc, parser, parse_args) != 0)
                return -1;
        }
        break;
    case YOML_TYPE_MAPPING:
        for (i = 0; i != (*target)->data.mapping.size; ++i) {
            if (yoml__resolve_alias(&(*target)->data.mapping.elements[i].key, doc, parser, parse_args) != 0)
                return -1;
            if (yoml__resolve_alias(&(*target)->data.mapping.elements[i].value, doc, parser, parse_args) != 0)
                return -1;
        }
        break;
    case YOML__TYPE_UNRESOLVED_ALIAS: {
        yoml_t *node = yoml_find_anchor(doc, (*target)->data.alias);
        if (node == NULL) {
            if (parser != NULL) {
                parser->problem = "could not resolve the alias";
                parser->problem_mark.line = (*target)->line;
                parser->problem_mark.column = (*target)->column;
            }
            return -1;
        }
        yoml_free(*target, parse_args->mem_set);
        *target = node;
        ++node->_refcnt;
    } break;
    }

    return 0;
}