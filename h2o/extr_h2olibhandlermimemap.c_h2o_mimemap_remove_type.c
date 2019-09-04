#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ khiter_t ;
typedef  char h2o_mimemap_type_t ;
struct TYPE_5__ {int /*<<< orphan*/  extmap; } ;
typedef  TYPE_1__ h2o_mimemap_t ;

/* Variables and functions */
 int /*<<< orphan*/  extmap ; 
 int /*<<< orphan*/  h2o_mem_release_shared (char*) ; 
 int /*<<< orphan*/  kh_del (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ kh_end (int /*<<< orphan*/ ) ; 
 scalar_t__ kh_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 char* kh_key (int /*<<< orphan*/ ,scalar_t__) ; 
 char* kh_val (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  on_unlink (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  rebuild_typeset (TYPE_1__*) ; 

void h2o_mimemap_remove_type(h2o_mimemap_t *mimemap, const char *ext)
{
    khiter_t iter = kh_get(extmap, mimemap->extmap, ext);
    if (iter != kh_end(mimemap->extmap)) {
        const char *key = kh_key(mimemap->extmap, iter);
        h2o_mimemap_type_t *type = kh_val(mimemap->extmap, iter);
        on_unlink(mimemap, type);
        h2o_mem_release_shared(type);
        kh_del(extmap, mimemap->extmap, iter);
        h2o_mem_release_shared((char *)key);
        rebuild_typeset(mimemap);
    }
}