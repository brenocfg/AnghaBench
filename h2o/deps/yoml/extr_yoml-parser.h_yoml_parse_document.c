#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yoml_t ;
struct TYPE_7__ {int /*<<< orphan*/  mem_set; } ;
typedef  TYPE_1__ yoml_parse_args_t ;
typedef  int /*<<< orphan*/  yaml_parser_t ;
typedef  int /*<<< orphan*/  yaml_event_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  YAML_NO_EVENT ; 
 int /*<<< orphan*/ * yoml__parse_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ yoml__resolve_alias (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ yoml__resolve_merge (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ yoml__resolve_tag (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  yoml_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline yoml_t *yoml_parse_document(yaml_parser_t *parser, yaml_event_type_t *unhandled, yoml_parse_args_t *parse_args)
{
    yoml_t *doc;

    /* parse */
    if ((doc = yoml__parse_node(parser, unhandled, parse_args)) == NULL) {
        return NULL;
    }
    if (unhandled != NULL)
        *unhandled = YAML_NO_EVENT;

    /* resolve tags, aliases and merge */
    if (yoml__resolve_tag(&doc, parser, parse_args) != 0)
        goto Error;
    if (yoml__resolve_alias(&doc, doc, parser, parse_args) != 0)
        goto Error;
    if (yoml__resolve_merge(&doc, parser, parse_args) != 0)
        goto Error;

    return doc;

Error:
    yoml_free(doc, parse_args->mem_set);
    return NULL;
}