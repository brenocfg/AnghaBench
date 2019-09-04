#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {size_t size; TYPE_4__* elements; } ;
struct TYPE_18__ {size_t size; int /*<<< orphan*/  elements; } ;
struct TYPE_21__ {TYPE_5__ mapping; TYPE_3__ sequence; } ;
struct TYPE_22__ {int type; TYPE_6__ data; int /*<<< orphan*/  column; int /*<<< orphan*/  line; int /*<<< orphan*/ * tag; } ;
typedef  TYPE_7__ yoml_t ;
struct TYPE_16__ {int /*<<< orphan*/  cb_arg; TYPE_7__* (* cb ) (int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_23__ {int /*<<< orphan*/  mem_set; TYPE_1__ resolve_tag; } ;
typedef  TYPE_8__ yoml_parse_args_t ;
struct TYPE_17__ {int /*<<< orphan*/  column; int /*<<< orphan*/  line; } ;
struct TYPE_24__ {char* problem; TYPE_2__ problem_mark; } ;
typedef  TYPE_9__ yaml_parser_t ;
struct TYPE_19__ {TYPE_7__* value; TYPE_7__* key; } ;

/* Variables and functions */
#define  YOML_TYPE_MAPPING 131 
#define  YOML_TYPE_SCALAR 130 
#define  YOML_TYPE_SEQUENCE 129 
#define  YOML__TYPE_UNRESOLVED_ALIAS 128 
 TYPE_7__* stub1 (int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yoml_free (TYPE_7__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int yoml__resolve_tag(yoml_t **target, yaml_parser_t *parser, yoml_parse_args_t *parse_args)
{
    size_t i;

    if (parse_args->resolve_tag.cb == NULL)
        return 0;

    if ((*target)->tag != NULL) {
        yoml_t *resolved = parse_args->resolve_tag.cb((*target)->tag, *target, parse_args->resolve_tag.cb_arg);
        if (resolved == NULL) {
            if (parser != NULL) {
                parser->problem = "tag resolution failed";
                parser->problem_mark.line = (*target)->line;
                parser->problem_mark.column = (*target)->column;
            }
            return -1;
        }
        yoml_free(*target, parse_args->mem_set);
        *target = resolved;
    }

    switch ((*target)->type) {
        case YOML_TYPE_SCALAR:
            break;
        case YOML_TYPE_SEQUENCE:
            for (i = 0; i != (*target)->data.sequence.size; ++i) {
                if (yoml__resolve_tag((*target)->data.sequence.elements + i, parser, parse_args) != 0)
                    return -1;
            }
            break;
        case YOML_TYPE_MAPPING:
            for (i = 0; i != (*target)->data.mapping.size; ++i) {
                if (yoml__resolve_tag(&(*target)->data.mapping.elements[i].key, parser, parse_args) != 0)
                    return -1;
                if (yoml__resolve_tag(&(*target)->data.mapping.elements[i].value, parser, parse_args) != 0)
                    return -1;
            }
            break;
        case YOML__TYPE_UNRESOLVED_ALIAS:
            break;
    }

    return 0;
}