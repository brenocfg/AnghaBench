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
typedef  int /*<<< orphan*/  h2o_mem_pool_t ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  h2o_mem_clear_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mem_init_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_memis (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ h2o_uri_escape (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_uri_escape(void)
{
    h2o_mem_pool_t pool;
    h2o_mem_init_pool(&pool);

#define TEST(src, preserve, expected)                                                                                              \
    do {                                                                                                                           \
        h2o_iovec_t escaped = h2o_uri_escape(&pool, H2O_STRLIT(src), preserve);                                                    \
        ok(h2o_memis(escaped.base, escaped.len, H2O_STRLIT(expected)));                                                            \
    } while (0)

    TEST("abc", NULL, "abc");
    TEST("a/c", NULL, "a%2Fc");
    TEST("a/c", "/", "a/c");
    TEST("\xe3\x81\x82", NULL, "%E3%81%82");
    TEST("a\0!", NULL, "a%00!");
    TEST("a/\0!", "/", "a/%00!");

#undef TEST

    h2o_mem_clear_pool(&pool);
}