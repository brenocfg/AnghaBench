#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {size_t size; TYPE_5__** elements; } ;
struct TYPE_15__ {size_t size; TYPE_7__* elements; } ;
struct TYPE_17__ {TYPE_2__ sequence; TYPE_1__ mapping; int /*<<< orphan*/  scalar; } ;
struct TYPE_19__ {int type; int /*<<< orphan*/  column; int /*<<< orphan*/  line; TYPE_3__ data; } ;
typedef  TYPE_5__ yoml_t ;
struct TYPE_20__ {int /*<<< orphan*/  mem_set; } ;
typedef  TYPE_6__ yoml_parse_args_t ;
struct TYPE_21__ {TYPE_5__* value; TYPE_5__* key; } ;
typedef  TYPE_7__ yoml_mapping_element_t ;
struct TYPE_18__ {int /*<<< orphan*/  column; int /*<<< orphan*/  line; } ;
struct TYPE_22__ {char* problem; TYPE_4__ problem_mark; } ;
typedef  TYPE_8__ yaml_parser_t ;

/* Variables and functions */
#define  YOML_TYPE_MAPPING 131 
#define  YOML_TYPE_SCALAR 130 
#define  YOML_TYPE_SEQUENCE 129 
#define  YOML__TYPE_UNRESOLVED_ALIAS 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  yoml__merge (TYPE_5__**,size_t,TYPE_5__*) ; 
 int /*<<< orphan*/  yoml_free (TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int yoml__resolve_merge(yoml_t **target, yaml_parser_t *parser, yoml_parse_args_t *parse_args)
{
    size_t i, j;

    switch ((*target)->type) {
    case YOML_TYPE_SCALAR:
        break;
    case YOML_TYPE_SEQUENCE:
        for (i = 0; i != (*target)->data.sequence.size; ++i) {
            if (yoml__resolve_merge((*target)->data.sequence.elements + i, parser, parse_args) != 0)
                return -1;
        }
        break;
    case YOML_TYPE_MAPPING:
        if ((*target)->data.mapping.size != 0) {
            i = (*target)->data.mapping.size;
            do {
                --i;
                if (yoml__resolve_merge(&(*target)->data.mapping.elements[i].key, parser, parse_args) != 0)
                    return -1;
                if (yoml__resolve_merge(&(*target)->data.mapping.elements[i].value, parser, parse_args) != 0)
                    return -1;
                if ((*target)->data.mapping.elements[i].key->type == YOML_TYPE_SCALAR &&
                    strcmp((*target)->data.mapping.elements[i].key->data.scalar, "<<") == 0) {
                    /* erase the slot (as well as preserving the values) */
                    yoml_mapping_element_t src = (*target)->data.mapping.elements[i];
                    memmove((*target)->data.mapping.elements + i, (*target)->data.mapping.elements + i + 1,
                            ((*target)->data.mapping.size - i - 1) * sizeof((*target)->data.mapping.elements[0]));
                    --(*target)->data.mapping.size;
                    /* merge */
                    if (src.value->type == YOML_TYPE_SEQUENCE) {
                        for (j = 0; j != src.value->data.sequence.size; ++j)
                            if (yoml__merge(target, i, src.value->data.sequence.elements[j]) != 0) {
                            MergeError:
                                if (parser != NULL) {
                                    parser->problem = "value of the merge key MUST be a mapping or a sequence of mappings";
                                    parser->problem_mark.line = src.key->line;
                                    parser->problem_mark.column = src.key->column;
                                }
                                return -1;
                            }
                    } else {
                        if (yoml__merge(target, i, src.value) != 0)
                            goto MergeError;
                    }
                    /* cleanup */
                    yoml_free(src.key, parse_args->mem_set);
                    yoml_free(src.value, parse_args->mem_set);
                }
            } while (i != 0);
        }
        break;
    case YOML__TYPE_UNRESOLVED_ALIAS:
        assert(!"unreachable");
        break;
    }

    return 0;
}