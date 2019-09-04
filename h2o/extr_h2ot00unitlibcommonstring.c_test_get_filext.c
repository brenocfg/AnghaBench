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
struct TYPE_3__ {int /*<<< orphan*/ * base; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 TYPE_1__ h2o_get_filext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_memis (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_get_filext(void)
{
    h2o_iovec_t ext;

    ext = h2o_get_filext(H2O_STRLIT("/abc.txt"));
    ok(h2o_memis(ext.base, ext.len, H2O_STRLIT("txt")));
    ext = h2o_get_filext(H2O_STRLIT("/abc.txt.gz"));
    ok(h2o_memis(ext.base, ext.len, H2O_STRLIT("gz")));
    ext = h2o_get_filext(H2O_STRLIT("/abc."));
    ok(h2o_memis(ext.base, ext.len, H2O_STRLIT("")));
    ext = h2o_get_filext(H2O_STRLIT("/abc"));
    ok(ext.base == NULL);
    ext = h2o_get_filext(H2O_STRLIT("/abc.def/abc"));
    ok(ext.base == NULL);
    ext = h2o_get_filext(H2O_STRLIT("/abc.def/"));
    ok(ext.base == NULL);
}