#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_mimemap_type_t ;
typedef  int /*<<< orphan*/  h2o_mimemap_t ;
typedef  int /*<<< orphan*/  h2o_globalconf_t ;

/* Variables and functions */
 int /*<<< orphan*/ * create_dynamic_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mem_release_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_default_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_type (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

h2o_mimemap_type_t *h2o_mimemap_define_dynamic(h2o_mimemap_t *mimemap, const char **exts, h2o_globalconf_t *globalconf)
{
    /* FIXME: fix memory leak introduced by this a cyclic link (mimemap -> new_type -> mimemap)
     * note also that we may want to update the reference from the dynamic type to the mimemap as we clone the mimemap,
     * but doing so naively would cause unnecessary copies of fastcgi.spawns... */
    h2o_mimemap_type_t *new_type = create_dynamic_type(globalconf, mimemap);
    size_t i;

    for (i = 0; exts[i] != NULL; ++i) {
        if (exts[i][0] == '\0') {
            /* empty string means default */
            set_default_type(mimemap, new_type);
        } else {
            set_type(mimemap, exts[i], new_type);
        }
    }
    h2o_mem_release_shared(new_type);
    return new_type;
}