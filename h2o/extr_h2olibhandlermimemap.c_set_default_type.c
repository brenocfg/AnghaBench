#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_mimemap_type_t ;
struct TYPE_6__ {int /*<<< orphan*/ * default_type; } ;
typedef  TYPE_1__ h2o_mimemap_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_mem_addref_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mem_release_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_link (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_unlink (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rebuild_typeset (TYPE_1__*) ; 

void set_default_type(h2o_mimemap_t *mimemap, h2o_mimemap_type_t *type)
{
    /* unlink the old one */
    on_unlink(mimemap, mimemap->default_type);
    h2o_mem_release_shared(mimemap->default_type);

    /* update */
    h2o_mem_addref_shared(type);
    mimemap->default_type = type;
    on_link(mimemap, type);
    rebuild_typeset(mimemap);
}