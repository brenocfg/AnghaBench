#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * scalar; } ;
struct TYPE_7__ {scalar_t__ type; int /*<<< orphan*/  _refcnt; TYPE_1__ data; int /*<<< orphan*/ * tag; } ;
typedef  TYPE_2__ yoml_t ;
typedef  int /*<<< orphan*/  resolve_tag_arg_t ;
struct TYPE_8__ {int /*<<< orphan*/ * base; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIZE_MAX ; 
 scalar_t__ YOML_TYPE_SCALAR ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 char* getenv (int /*<<< orphan*/ *) ; 
 TYPE_5__ h2o_strdup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static yoml_t *resolve_env_tag(yoml_t *node, resolve_tag_arg_t *arg)
{
    if (node->type != YOML_TYPE_SCALAR) {
        fprintf(stderr, "value of !env must be a scalar");
        return NULL;
    }

    const char *value;
    if ((value = getenv(node->data.scalar)) == NULL)
        value = "";

    /* free old data (we need to reset tag; otherwise we might try to resolve the value once again if the same object is referred
     * more than once due to the use of aliases) */
    free(node->data.scalar);
    free(node->tag);
    node->tag = NULL;

    node->data.scalar = h2o_strdup(NULL, value, SIZE_MAX).base;
    ++node->_refcnt;

    return node;
}