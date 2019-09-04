#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_mimemap_t ;
struct TYPE_3__ {int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ h2o_globalconf_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_mem_release_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * h2o_mimemap_create () ; 
 int /*<<< orphan*/  h2o_mimemap_define_dynamic (int /*<<< orphan*/ *,char const**,TYPE_1__*) ; 

__attribute__((used)) static void test_dynamic()
{
    h2o_mimemap_t *mimemap = h2o_mimemap_create();
    const char *exts[] = {".php", NULL};
    h2o_globalconf_t global = {NULL};
    h2o_mimemap_define_dynamic(mimemap, exts, &global);
    h2o_mem_release_shared(mimemap);
}