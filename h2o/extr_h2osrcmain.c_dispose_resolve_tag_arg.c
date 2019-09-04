#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* base; } ;
struct TYPE_9__ {int /*<<< orphan*/  node; TYPE_1__ filename; } ;
typedef  TYPE_3__ resolve_tag_node_cache_entry_t ;
struct TYPE_8__ {size_t size; TYPE_3__* entries; } ;
struct TYPE_10__ {TYPE_2__ node_cache; } ;
typedef  TYPE_4__ resolve_tag_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  yoml_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dispose_resolve_tag_arg(resolve_tag_arg_t *arg)
{
    size_t i;
    for (i = 0; i != arg->node_cache.size; ++i) {
        resolve_tag_node_cache_entry_t *cached = arg->node_cache.entries + i;
        free(cached->filename.base);
        yoml_free(cached->node, NULL);
    }
    free(arg->node_cache.entries);
}