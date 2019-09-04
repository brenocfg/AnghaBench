#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
struct TYPE_16__ {char* scalar; } ;
struct TYPE_19__ {scalar_t__ type; int /*<<< orphan*/  _refcnt; TYPE_1__ data; } ;
typedef  TYPE_4__ yoml_t ;
struct TYPE_18__ {TYPE_7__* member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_20__ {char* member_0; TYPE_3__ member_2; int /*<<< orphan*/ * member_1; } ;
typedef  TYPE_5__ yoml_parse_args_t ;
struct TYPE_17__ {int /*<<< orphan*/  base; } ;
struct TYPE_21__ {TYPE_4__* member_1; int /*<<< orphan*/  member_0; TYPE_4__* node; TYPE_2__ filename; } ;
typedef  TYPE_6__ resolve_tag_node_cache_entry_t ;
struct TYPE_15__ {size_t size; TYPE_6__* entries; } ;
struct TYPE_22__ {TYPE_14__ node_cache; } ;
typedef  TYPE_7__ resolve_tag_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIZE_MAX ; 
 scalar_t__ YOML_TYPE_SCALAR ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  h2o_strdup (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_vector_reserve (int /*<<< orphan*/ *,TYPE_14__*,size_t) ; 
 TYPE_4__* load_config (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  resolve_tag ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static yoml_t *resolve_file_tag(yoml_t *node, resolve_tag_arg_t *arg)
{
    size_t i;
    yoml_t *loaded;

    if (node->type != YOML_TYPE_SCALAR) {
        fprintf(stderr, "value of the !file node must be a scalar");
        return NULL;
    }

    char *filename = node->data.scalar;

    /* check cache */
    for (i = 0; i != arg->node_cache.size; ++i) {
        resolve_tag_node_cache_entry_t *cached = arg->node_cache.entries + i;
        if (strcmp(filename, cached->filename.base) == 0) {
            ++cached->node->_refcnt;
            return cached->node;
        }
    }

    yoml_parse_args_t parse_args = {
        filename,          /* filename */
        NULL,              /* mem_set */
        {resolve_tag, arg} /* resolve_tag */
    };
    loaded = load_config(&parse_args, node);

    if (loaded != NULL) {
        /* cache newly loaded node */
        h2o_vector_reserve(NULL, &arg->node_cache, arg->node_cache.size + 1);
        resolve_tag_node_cache_entry_t entry = {h2o_strdup(NULL, filename, SIZE_MAX), loaded};
        arg->node_cache.entries[arg->node_cache.size++] = entry;
        ++loaded->_refcnt;
    }

    return loaded;
}